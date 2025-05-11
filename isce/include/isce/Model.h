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

namespace json = boost::json;

class Model {
public:
  static inline PGconn* connection;
  Model() {

    conn = PQconnectdb(create_conn_str(json_from_file("config.json")).c_str());
    connection = conn;
    if (PQstatus(conn) != CONNECTION_OK) {
      std::cerr << "Connected error: " << PQerrorMessage(conn) << std::endl;
    }

  }

  ~Model() {
    if (conn) {
      PQfinish(conn);
    }
  }

  // UPDATED <<< create how to create on laravel/php 
  void create(std::string table_name, std::vector<std::string>columns, std::vector<std::string>parameters) {

    if (columns.size() != parameters.size()) {
      std::cerr << "Error number of columns and parameters must match" << std::endl;
    }

    std::string query = std::format("INSERT INTO {} (", table_name);


    for (size_t i = 0; i < columns.size(); ++i) {
      query += columns[i];
      if (i != columns.size() - 1) {
        query += ", ";
      }
    }

    query += ") VALUES (";

    for (size_t i = 0; i < parameters.size(); ++i) {
      query += "'" + parameters[i] + "'";
      if (i != parameters.size() - 1) {
        query += ", ";
      }
    }

    query += ");";

    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "created error" << PQerrorMessage(conn) << std::endl;
    }

    PQclear(res);

  }

  void update(std::string table_name, std::string new_value, std::string condition) {
    std::string query = "UPDATE " + table_name + " SET " + new_value + " WHERE id =" + condition + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "updated error" << PQerrorMessage(conn) << std::endl;
    }

    PQclear(res);

  }

  void delete_(std::string table_name, std::string condition) {
    std::string query = "DELETE FROM " + table_name + " WHERE id =" + condition + ';';
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "deleted error" << PQerrorMessage(conn) << std::endl;
    }

    PQclear(res);

  }

  bool find(std::string table_name, int id) {
    std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
      PQclear(res);
      std::cerr << "user not found" << PQerrorMessage(conn) << std::endl;
      return false;

      PQclear(res);
    }
    else {

      return true;
    }

    PQclear(res);


  }

  bool findOrfail(std::string table_name, int id) {
    std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {

      throw std::runtime_error("user not found");
      return false;
      PQclear(res);
    }

    return true;


    PQclear(res);
  }


  bool where_(std::string table_name, std::string column, std::string parameter) {
    std::string query = "SELECT * FROM " + table_name + " WHERE " + column + "=" + parameter;

    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
      PQclear(res);
      throw std::runtime_error("user not found");
      return false;
    }

    return true;
    PQclear(res);

  }

private:
  PGconn* conn;

  json::object json_from_file(const std::string file_name) {
    std::fstream input(file_name);

    std::stringstream buffer;

    buffer << input.rdbuf();

    return json::parse(buffer.str()).as_object();

  }

  std::string create_conn_str(const json::object& db_config) {
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
