#include "isce/Model.h"
#include "isce/DataBase.h"
#include "seeder.h"
#include <libpq-fe.h>


class WallSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO wall (name, is_group, is_public) VALUES
    ('Tech Talk', 1, 1),
    ('Private Notes', 0, 0),
    ('Developers Hub', 1, 0),
    ('My Personal Wall', 0, 1),
    ('Study Group', 1, 1),
    ('Travel Blog', 0, 1),
    ('Cooking Tips', 0, 1),
    ('Secret Project', 1, 0),
    ('Gaming Community', 1, 1),
    ('Book Club', 1, 0);
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};