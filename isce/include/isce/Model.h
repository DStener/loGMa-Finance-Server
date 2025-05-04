#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <libpq-fe.h>

class Model {

public:
  Model() {
    conn = PQconnectdb("host=localhost dbname=*** user=*** password=***");

    if (PQstatus(conn) != CONNECTION_OK) {
      std::cerr << "Connected error: " << PQerrorMessage(conn) << std::endl;
    }

  }

  ~Model() {
    if (conn) {
      PQfinish(conn);
    }
  }


  void create(std::string table_name, std::string parameters) {
    std::string query = "CREATE TABLE " + table_name + "(" + "id serial primary key, " + parameters + ");";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "created error" << PQerrorMessage(conn) << std::endl;
    }

    PQclear(res);

  }

  void update(std::string table_name, std::string new_value, std::string condition) {
    std::string query = "UPDATE " + table_name + " SET " + new_value + " WHERE " + condition + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "updated error" << PQerrorMessage(conn) << std::endl;
    }

    PQclear(res);

  }

  static void delete_(std::string table_name) {
    //
  }

  static void findOrfail() {
    //
  }

private:
  PGconn* conn;


};
