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

#include <boost/algorithm/string/join.hpp>

namespace json = boost::json;

using rec_t = std::pair<std::string, std::string>;
using row_t = std::vector<rec_t>;

using response_vec_t = std::vector<row_t>;


class Model {
public:
  Model() {

    Model::init_connection();
  }

  ~Model() {
    Model::close_connection();

  }

  size_t create(std::string table_name, std::vector<std::string>columns, std::vector<std::string>parameters) {

    if (columns.size() != parameters.size()) {
      std::cerr << "Error number of columns and parameters must match" << std::endl;
      return;
    }

    std::string query = std::format("INSERT INTO {} ({}) VALUES ({}) RETURNING id",
                                    table_name,
                                    boost::join(columns, ", "),
                                    boost::join(parameters, ", "));

    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << PQerrorMessage(Model::get_connection()) << std::endl;
      PQclear(res);
      throw std::runtime_error("user not found");
    }

    auto id = PQgetvalue(res, 0, 0);

    PQclear(res);

    return std::stoul(id);

  }

  void update(std::string table_name, std::string new_value, std::string condition) { 
    std::string query = "UPDATE " + table_name + " SET " + new_value + " WHERE " + condition + ";";
    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "updated error" << PQerrorMessage(connection) << std::endl;
    }

    PQclear(res);

  }

  void delete_(std::string table_name, std::string condition) {
    std::string query = "DELETE FROM " + table_name + " WHERE " + condition + ';'; 
    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "deleted error" << PQerrorMessage(connection) << std::endl;
    }

    PQclear(res);

  }

  response_vec_t find(std::string table_name, std::string condition) {
    std::string query = "SELECT * FROM " + table_name + " WHERE " + condition + ";";
    PGresult* res = PQexec(connection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cout << PQerrorMessage(Model::get_connection()) << std::endl;
      PQclear(res);
      throw std::runtime_error("user not found");
    }
    
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


  bool where_(std::string table_name, std::string column, std::string parameter) {
    std::string query = "SELECT * FROM " + table_name + " WHERE " + column + "= '"  + parameter + "'";

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

private:
  static inline PGconn* connection = nullptr;
  

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
