#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class WallSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO wall (name, is_group, is_public, lim) VALUES
    ('Ivan Ivanov', false, true, 100000),
    ('Elena Petrova', false, true, 150000),
    ('Developers Group', true, false, 500000),
    ('Photography Club', true, true, 250000),
    ('Private Diary', false, false, 75000);
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};