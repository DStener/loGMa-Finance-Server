#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class WallSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO wall (name, is_group, is_public) VALUES
    ('Ivan Ivanov', false, true),
    ('Elena Petrova', false, true),
    ('Developers Group', true, false),
    ('Photography Club', true, true),
    ('Private Diary', false, false);
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};