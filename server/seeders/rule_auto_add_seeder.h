#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class RuleAutoAddSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO rule_auto_add (id_category, id_wall) VALUES
    (1, 1),
    (2, 1),
    (3, 2),
    (4, 3),
    (5, 2),
    (6, 4),
    (7, 1),
    (8, 4),
    (9, 2),
    (10, 3);
    )";



    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};