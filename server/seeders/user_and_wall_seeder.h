#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class UserAndWallSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO user_and_wall (id_user, id_wall, is_admin) VALUES
    (1, 1, true),
    (1, 2, false),
    (2, 1, false),
    (3, 3, true),
    (4, 4, false),
    (5, 2, true),
    (2, 5, false),
    (3, 4, false),
    (5, 5, false),
    (4, 3, true);
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};