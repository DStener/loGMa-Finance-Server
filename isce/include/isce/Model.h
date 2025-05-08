#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <libpq-fe.h>
#include <vector>


class Model {

public:
  static PGconn* connection;

  Model() {
    conn = PQconnectdb("host=localhost dbname=*** user=*** password=***");
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
  void create(std::string table_name, std::vector<std::string>columns,std::vector<std::string>parameters) {
    
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
    std::string query = "UPDATE " + table_name + " SET " + new_value + " WHERE id =" +  condition + ";";
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

  void find(std::string table_name, int id) {
    std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
      PQclear(res);
      std::cerr << "user not found" << PQerrorMessage(conn) << std::endl;

      PQclear(res);
    }

    int fields = PQnfields(res);
    for (int i = 0; i < fields; ++i) {
      std::cout << PQfname(res, i) << ": " << PQgetvalue(res, 0, i) << std::endl;
    }

    PQclear(res);

  
  }

  void findOrfail(std::string table_name, int id) {
    std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
      PQclear(res);
      throw std::runtime_error("user not found");
    }

    int fields = PQnfields(res);
    for (int i = 0; i < fields; ++i) {
      std::cout << PQfname(res, i) << ": " << PQgetvalue(res, 0, i) << std::endl;
    }

    PQclear(res);
  }
  

private:
  PGconn* conn;


};
