#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <libpq-fe.h>

class Model {

public:
  Model(std::string table) : tableName(std::move(table)) {
    conn = PQconnectdb("host=localhost dbname=*** user=*** password=***");
    if (PQstatus(conn) != CONNECTION_OK) {
      std::cerr << "Connected error: " << PQerrorMessage(conn) << std::endl;
    }

  }

  virtual std::unordered_map<std::string, std::string>find(int id) {
    std::string query = "SELECT * FROM " + tableName + " WHERE id=" + std::to_string(id) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::string error = PQerrorMessage(conn);
      PQclear(res);
      throw std::runtime_error("SQL error" + error);
    }


    if (PQntuples(res) == 0) {
      PQclear(res);
      return {};
    }

    std::unordered_map<std::string, std::string> result;
    int cols = PQnfields(res);

    for (int i = 0; i < cols; ++i) {
      result[PQfname(res, i)] = PQgetvalue(res, 0, i);
    }

    PQclear(res);
    return result;

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
