#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class CategorySeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO category (icon, name, id_wall) VALUES
    (1001, 'Groceries', 1),
    (1002, 'Transport', 1),
    (1003, 'Entertainment', 2),
    (1004, 'Salary', 3),
    (1005, 'Gifts', 2),
    (1006, 'Education', 4),
    (1007, 'Utilities', 1),
    (1008, 'Healthcare', 4),
    (1009, 'Dining Out', 2),
    (1010, 'Subscriptions', 2);
    )";



    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};