#pragma once
#include <vector>
#include <iostream>

#include <libpq-fe.h>

#include <isce/Model.h>



class Schema {
public:
  static void create(std::string_view table_name, const std::vector<std::string>& columns) {
    Model::init_connection();  


    std::string sql = std::format("CREATE TABLE IF NOT EXISTS {} (id SERIAL PRIMARY KEY", table_name);
    for (const auto& column : columns) {
      sql += ", " + column;
    }
    sql += ");";

    
    PGresult* res = PQexec(Model::get_connection(), sql.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "Error creating table: " << PQerrorMessage(Model::get_connection()) << std::endl;
    }
    else {
      std::cout << "Table " << table_name << " created successfully.\n";
    }
    
    PQclear(res);
  }
};
