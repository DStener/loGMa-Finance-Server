#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class СurrencySeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO currency (name, sign) VALUES
    ('Ruble', 'R'),
    ('Dollar', 'D'),
    ('Euro', 'E');
    )";



    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};