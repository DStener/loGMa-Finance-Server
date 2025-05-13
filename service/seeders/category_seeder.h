#include "isce/Model.h"
#include "isce/DataBase.h"
#include "seeder.h"
#include <libpq-fe.h>


class CategorySeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO category (icon, name, id_wall) VALUES
    (101, 'Announcements', 1),
    (102, 'General Discussion', 1),
    (103, 'Ideas & Suggestions', 2),
    (104, 'Personal Notes', 2),
    (105, 'Development', 3),
    (106, 'Bugs & Issues', 3),
    (107, 'Travel Logs', 6),
    (108, 'Recipes', 7),
    (109, 'Secret Plans', 8),
    (110, 'Book Reviews', 10);
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};