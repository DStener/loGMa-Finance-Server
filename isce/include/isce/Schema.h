#pragma once
#include <vector>
#include <iostream>

#include <libpq-fe.h>

#include <isce/Model.h>
#include <isce/DataBase.h>


class Schema {
public:
  void up();

  static void create(std::string_view&& table_name, std::vector<std::string> columns ) {
    
    std::string sql = std::format("CREATE TABLE IF NOT EXISTS {} (id SERIAL PRIMARY KEY",
                                  table_name);

    for (const auto& i : columns) {
      sql += ", " + i;

    }
    sql += ");";

    PGresult* res = PQexec(Model::connection, sql.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "error" << PQerrorMessage(Model::connection) << std::endl;
    }

  }


};