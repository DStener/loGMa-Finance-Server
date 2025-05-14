#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class OperationAndCategorySeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO operation_and_category (id_operation, id_category) VALUES
    (1, 2),
    (1, 3),
    (2, 1),
    (3, 2),
    (4, 1),
    (4, 3),
    (5, 2),
    (6, 4),
    (7, 1),
    (8, 3);
    )";

    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};