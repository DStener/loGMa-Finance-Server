#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class CurrencyAndWallSeeder : public Seeder{
public:
  
  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO currency_and_wall (id_wall, id_currency) VALUES
    (1, 1),
    (1, 2),
    (2, 1),
    (2, 3),
    (3, 2),
    (3, 3);
    )";


     PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};