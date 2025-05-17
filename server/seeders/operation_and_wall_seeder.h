#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class OperationAndWallSeedr : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    // std::string query = R"(
    // INSERT INTO operation_and_wall (id_operation, id_wall) VALUES
    // (1, 1),
    // (2, 1),
    // (3, 2),
    // (4, 2),
    // (5, 3),
    // (6, 3),
    // (7, 4),
    // (8, 4),
    // (9, 5),
    // (10, 5);
    // )";

    // PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};