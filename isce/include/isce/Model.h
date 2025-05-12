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

#include "config.h"
#include <isce/DTO.h>

#include <boost/algorithm/string/join.hpp>

namespace json = boost::json;

using rec_t = std::pair<std::string, std::string>;
using row_t = std::vector<rec_t>;

using response_vec_t = std::vector<row_t>;

#define DB_CHECK_ERROR(condition) 																		 \
	if(condition) {																											 \
		std::string error = std::format("{}, func {}(), line {}: {}", 		 \
																		__FILE__, __FUNCTION__, __LINE__,  \
																		PQerrorMessage(Model::get_connection()));\
		throw std::runtime_error(error);																	 \
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

  bool update(std::vector<std::string> new_values, std::vector<std::string> conditions) {
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

    return update_str > 0;

    PQclear(res);

  }

  bool delete_(std::string condition) {
    std::string query = "DELETE FROM " + table_name_ + " WHERE id=" + condition + ';'; 

    PGresult* res = PQexec(connection, query.c_str());
    DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK)

    auto delete_str = std::stoi(PQcmdTuples(res));

    return delete_str > 0;
    
    PQclear(res);

  }

  response_vec_t find(std::string condition) {
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

  bool where_(std::string column, std::string parameter) {
    std::string query = "SELECT * FROM " + table_name_ + " WHERE " + column + "= '"  + parameter + "'";

    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << PQerrorMessage(Model::get_connection()) << std::endl;
      PQclear(res);
      throw std::runtime_error("user not found");
    }

    int rows = PQntuples(res);

    PQclear(res);
    return rows != 0;
  }


  static void init_connection() {
    if (connection == nullptr) {
      auto config = json_from_file(CONFIG_PATH);
      std::string conn_str = create_conn_str(config);

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

    std::vector<std::string> colums;
    std::vector<std::string> values;

    DTO::for_each(t, [&](std::string_view&& name, auto& field) {
      colums.push_back(name.data());
      values.push_back(DTO::to_string(field));
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

  template<typename T>
  resp_vec_t<T> find(std::string condition) {

    resp_vec_t<T> out;
    std::string query = std::format("SELECT * FROM {} WHERE {}",
      table_name_, condition);

    PGresult* res = PQexec(connection, query.c_str());
    DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

      int rows = PQntuples(res);
    int cols = PQnfields(res);

    std::cout << rows << " " << cols << std::endl;

    for (int i = 0; i < rows; ++i) {
      T t;

      DTO::for_each(t, [&](std::string_view&& name, auto& field) {
        int index = PQfnumber(res, name.data());
        if (index == -1) { return; } // if not found

        const auto value = PQgetvalue(res, i, index);

        field = value; // [FIXME]
        });

      out.push_back(std::make_pair(i + 1, std::move(t)));
    }

    return out;
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

  static std::string create_conn_str(const json::object& db_config) {
    std::string conn_str;

    if (db_config.contains("host")) {
      conn_str += "host=" + json::value_to<std::string>(db_config.at("host")) + " ";
    }
    if (db_config.contains("dbname")) {
      conn_str += "dbname=" + json::value_to<std::string>(db_config.at("dbname")) + " ";
    }
    if (db_config.contains("user")) {
      conn_str += "user=" + json::value_to<std::string>(db_config.at("user")) + " ";
    }
    if (db_config.contains("password")) {
      conn_str += "password=" + json::value_to<std::string>(db_config.at("password")) + " ";
    }



    return conn_str;
  }

  

};
