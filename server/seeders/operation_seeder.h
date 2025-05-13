#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>


class OperationSeedr : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = R"(
    INSERT INTO operation (value, id_currency, id_user) VALUES
    (150000, 1, 1),
    (-5000, 1, 1),      
    (123456, 2, 2),     
    (-3456, 2, 2),      
    (98765, 3, 3),      
    (-8765, 3, 3),      
    (250000, 4, 4),     
    (-12000, 4, 4),     
    (100000, 5, 5),     
    (-9999, 5, 5);      
    )";


    PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};