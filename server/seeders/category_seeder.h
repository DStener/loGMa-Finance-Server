#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class CategorySeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();
    std::string query = R"(
    INSERT INTO category (icon, name, id_wall, limits) VALUES
    (1001, 'Groceries', 1, 5000),
    (1002, 'Transport', 2, 3000),
    (1003, 'Entertainment', 3, 2000),
    (1004, 'Salary', 4, 10000),
    (1005, 'Gifts', 5, 1500),
    (1006, 'Education', 1, 4000),
    (1007, 'Utilities', 2, 2500),
    (1008, 'Healthcare', 3, 3500),
    (1009, 'Dining Out', 4, 1800),
    (1010, 'Subscriptions', 5, 1200);
    )";



     PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};