#pragma once

#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>

class UserSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    // std::string query = R"(
    // INSERT INTO users (login, name, surname, patronymic, birthday, password) VALUES
    // ('ivanov123', 'Ivan', 'Ivanov', 'Ivanovich', '1990-05-15', '123'),
    // ('petrova89', 'Elena', 'Petrova', 'Sergeevna', '1989-11-23', '321'),
    // ('sergey_77', 'Sergey', 'Smirnov', 'Nikolaevich', '1977-03-10', '213'),
    // ('katya2020', 'Ekaterina', 'Volkova', 'Igorevna', '2000-07-30', '312'),
    // ('nikita_dev', 'Nikita', 'Kuznetsov', 'Alekseevich', '1995-01-05', '124');
    // )";

    // PGresult* res = PQexec(Model::get_connection(), query.c_str());

  }

};