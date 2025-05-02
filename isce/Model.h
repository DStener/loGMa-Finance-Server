#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <libpq-fe.h>

class Model {

public:
  Model(std::string table) : tableName(table) {
    conn = PQconnectdb("host=localhost dbname=*** user=*** password=***");
    if (PQstatus(conn) != CONNECTION_OK) {
      std::cerr << "Connected error: " << PQerrorMessage(conn) << std::endl;
    }

  }

  template<typename T>
  static void create(std::string table_name, std::string parameters) {
    std::string query = "CREATE TABLE " + table_name + "(" + "id serial primary key " + parameters + ");";
    std::unique_ptr<PGresult> result = PQexec(conn, query.c_str());

    if (PQresultStatus != PGRES_TUPLES_OK) {
      std::cerr << "cretae table filid " << PQerrorMessage(conn) << std::endl;
    }

  }
  
  static void update() {
  
  }

  static void delete_() {
  
  }


  ~Model() {
    if (conn) {
      PQfinish(conn);
    }
    conn = nullptr;
  }

protected:
  std::string tableName;
  PGconn* conn;

};
