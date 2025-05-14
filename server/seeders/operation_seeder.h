#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class OperationSeedr : public Seeder{
public:

  static void run() {
    
    Model::init_connection();
    
    // std::string query = R"(
    // INSERT INTO operation (value, id_currency, id_user) VALUES
    // (10000, 1, 1),
    // (-22500, 2, 2),
    // (-50000, 1, 3),
    // (-999999, 3, 4),
    // (120000, 2, 5);
    // )";


    // PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};