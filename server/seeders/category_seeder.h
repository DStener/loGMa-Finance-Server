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
    (1002, 'Transport', 2),
    (1003, 'Entertainment', 3),
    (1004, 'Salary', 4),
    (1005, 'Gifts', 5),
    (1006, 'Education', 1),
    (1007, 'Utilities', 2),
    (1008, 'Healthcare', 3),
    (1009, 'Dining Out', 4),
    (1010, 'Subscriptions', 5);
    )";



    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};