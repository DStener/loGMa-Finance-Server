#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <libpq-fe.h>
#include <vector>
#include <fstream>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <sstream>
#include <format>

#include "config.h"
#include <isce/DTO.h>

#include <boost/algorithm/string/join.hpp>

using namespace isce;

namespace json = boost::json;

using rec_t = std::pair<std::string, std::string>;
using row_t = std::vector<rec_t>;

using response_vec_t = std::vector<row_t>;

#define DB_CHECK_ERROR(condition) 																		 \
	if(condition) {																											 \
		std::string error = std::format("{}, func {}(), line {}: {}", 		 \
																		__FILE__, __FUNCTION__, __LINE__,  \
																		PQerrorMessage(Model::get_connection()));\
		std::cerr << error << std::endl;													 \
	}

#define DB_CHECK_MESSAGE(condition)                                    \
  if (condition) {                                                     \
    return PQerrorMessage(Model::get_connection());                    \
  }

class Model {
public:

  Model(std::string tabel_name) : table_name_(tabel_name) {

    Model::init_connection();
  }

  ~Model() {
    Model::close_connection();

  }

  size_t create(std::vector<std::string>columns, std::vector<std::string>parameters) {
    try {
      if (columns.size() != parameters.size()) {
        std::cerr << "Error number of columns and parameters must match" << std::endl;
        return 1;
      }

      std::string query = std::format("INSERT INTO {} ({}) VALUES ('{}') RETURNING id",
        table_name_,
        boost::join(columns, ", "),
        boost::join(parameters, "', '"));


      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

        auto id = PQgetvalue(res, 0, 0);

      try {
        return std::stoul(id);
      }
      catch (const std::invalid_argument& e) {
        PQclear(res);

        std::cerr << "error" << e.what() << std::endl;
        throw std::runtime_error("Invalid id format returned");
      }

    
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
    
  }

  bool update(std::vector<std::string> new_values, std::vector<std::string> conditions) {
    try {

      std::string query = "UPDATE " + table_name_ + " SET ";

      for (size_t i = 0; i < new_values.size(); ++i) {
        query += new_values[i];
        if (i != new_values.size() - 1)
          query += ", ";
      }

      query += " WHERE ";

      for (size_t i = 0; i < conditions.size(); ++i) {
        query += conditions[i];
        if (i != conditions.size() - 1)
          query += " AND ";
      }

      query += ";";

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK)

        auto update_str = std::stoi(PQcmdTuples(res));

      PQclear(res);
      return update_str > 0;
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }

  bool delete_(std::string condition) {
    try {
      std::string query = "DELETE FROM " + table_name_ + " WHERE id=" + condition + ';';

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK)

        auto delete_str = std::stoi(PQcmdTuples(res));

      PQclear(res);
      return delete_str > 0;
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }
  bool cdelete(std::string condition) {
    try {

      std::string query = std::format("DELETE FROM {} WHERE {};",
        table_name_, condition);

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK)

        auto delete_str = std::stoi(PQcmdTuples(res));

      PQclear(res);
      return delete_str > 0;
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }

  response_vec_t find(std::string condition) {
    try {

      std::string query = "SELECT * FROM " + table_name_ + " WHERE " + condition + ";";

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

        response_vec_t vec;


      int rows = PQntuples(res);
      int cols = PQnfields(res);

      for (size_t i = 0; i < rows; i++)
      {
        row_t row;
        for (size_t j = 0; j < cols; j++)
        {
          auto value = PQgetvalue(res, i, j);
          auto field = PQfname(res, j);

          row.push_back(std::make_pair(field, value));
        }

        vec.push_back(row);

      }

      PQclear(res);
      return vec;
    }
    catch (std::exception e) {
      std::cerr << "some error" << e.what() << std::endl;
      return {};

    }
  }

  bool where_(std::string column, std::string parameter) {
    std::string query = "SELECT * FROM " + table_name_ + " WHERE " + column + "= '"  + parameter + "'";

    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << PQerrorMessage(Model::get_connection()) << std::endl;
      PQclear(res);
      throw std::runtime_error("error");
    }

    int rows = PQntuples(res);

    PQclear(res);
    return rows != 0;
  }


  static void init_connection() {
    if (connection == nullptr) {
     const auto conn_str = pgconnect();

      connection = PQconnectdb(conn_str.c_str());

      if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
        connection = nullptr;
      }
    }
  }

  static PGconn* get_connection() {
    return connection;
  }

  static void close_connection() {
    if (connection) {
      PQfinish(connection);
      connection = nullptr;
    }
  }

  ///////////////// DTO FUNCTIONS /////////////////////

  template <typename T>
  size_t create(const T& t) {
    try {


      std::vector<std::string> colums;
      std::vector<std::string> values;

      DTO::for_each(t, [&](std::string_view&& name, auto& field) {

        const auto value = DTO::to_string(field);

        if (value == "''") { return; }

        colums.push_back(std::string{ name });
        values.push_back(value);
        });

      std::string query = std::format("INSERT INTO {} ({}) VALUES ({}) RETURNING id",
        table_name_,
        boost::join(colums, ", "),
        boost::join(values, ", "));

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

        auto id = PQgetvalue(res, 0, 0);

      PQclear(res);
      return std::stoul(id);
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }

  template <typename T>
  std::string update(const T& t, std::string condition) {
    try {

      std::vector<std::string> assigs;

      DTO::for_each(t, [&](std::string_view&& name, auto& field) {

        const auto value = DTO::to_string(field);

        if (value.empty()) { return; }

        assigs.push_back(std::format("{} = {}", name.data(), value));
        });

      std::string query = std::format("UPDATE {} SET {} WHERE {};",
        table_name_,
        boost::join(assigs, ", "),
        condition);

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_MESSAGE(PQresultStatus(res) != PGRES_COMMAND_OK)

        return {};
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }

  template<typename T>
  resp_vec_t<T> find(std::string condition) {
    try {


      resp_vec_t<T> out;
      std::string query = std::format("SELECT *, id as id_db FROM {} WHERE {}",
        table_name_, condition);

      PGresult* res = PQexec(connection, query.c_str());
      DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

        int rows = PQntuples(res);
      int cols = PQnfields(res);

      for (int i = 0; i < rows; ++i) {
        T t;

        DTO::for_each(t, [&](std::string_view&& name, auto& field) {
          int index = PQfnumber(res, name.data());
          if (index == -1) { return; } // if not found

          const auto value = PQgetvalue(res, i, index);
          // std::cout << 

          field = value; // [FIXME]
          });

        int id_index = PQfnumber(res, "id_db");
        const auto id = std::stol(PQgetvalue(res, i, id_index));

        out.push_back(std::make_pair(id, std::move(t)));
      }

      return out;
    }
    catch (std::exception e) {
      std::cerr << "error: " << e.what() << std::endl;
      return {};

    }
  }



private:
  static inline PGconn* connection = nullptr;
  std::string table_name_;

  static json::object json_from_file(const std::string file_name) {
    
    std::fstream input(file_name, std::ios::in);

    std::stringstream buffer;
    buffer << input.rdbuf();

    json::object temp = json::parse(buffer.str()).as_object();

    return temp.at("database").as_object();
  }

  static std::string pgconnect() {

    // If run in docker and has envirement variable
    if (const char* host_p = std::getenv("POSTGRES_HOST")) {
      return std::format("host={} dbname={} user={} password={}",
                          host_p, 
                          std::getenv("POSTGRES_DB"),
                          std::getenv("POSTGRES_USER"),
                          std::getenv("POSTGRES_PASSWORD"));
    }

    const auto database = json_from_file(CONFIG_PATH);

    return std::format("host={} dbname={} user={} password={}",
                        json::value_to<std::string>(database.at("host")),
                        json::value_to<std::string>(database.at("dbname")),
                        json::value_to<std::string>(database.at("user")),
                        json::value_to<std::string>(database.at("password")));
  }
};
