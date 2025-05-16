#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class OperationSeedr : public Seeder{
public:

  static void run() {
    
    Model::init_connection();
    
    std::string query = R"(
    INSERT INTO operation (value, iso_currency, id_user) VALUES
    (10000, 'USD', 1),
    (-22500, 'EUR', 2),
    (-50000, 'USD', 3),
    (-999999, 'JPY', 4),
    (120000, 'EUR', 5);
    )";


    // PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};