#pragma once
#include <libpq-fe.h>
#include "isce/Model.h"
#include "isce/DataBase.h"
#include <vector>
#include <iostream>

// example
/*
  Schema::create('users',{
    "name varchar(255)",
    "email varchar(255)",
    "age integer"
  });
*/

class Schema {
  static void create(std::string table_name,const std::vector<std::string> columns ) {
    
    std::string sql = "CREATE TABLE " + table_name + " (id SERIAL PRIMARY KEY";

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