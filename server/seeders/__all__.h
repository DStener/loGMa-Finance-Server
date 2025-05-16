#pragma once 

#include "users_seeder.h"
#include "seeders/category_seeder.h"
#include "seeders/user_and_wall_seeder.h"
#include "seeders/operation_seeder.h"
#include "seeders/operation_and_wall_seeder.h"
#include "seeders/currency_seeder.h"
#include "seeders/rule_auto_add_seeder.h"
#include "seeders/operation_and_category_seeder.h"
#include "seeders/wall_seeder.h"
#include "seeders/file_seeder.h"
//#include "seeders/currency_and_wall_seeder.h"

#define RUN_ALL_SEEDERS AllSeeders::run();

class AllSeeders {
public:
    static void run() {
        
        UserSeeder::run();                  // 0 users
        /* ... */                           // 1 token
        FileSeeder::run();                  // 2 file;
        CurrencySeeder::run();              // 3 currency 
        OperationSeedr::run();              // 4 operaion 
        WallSeeder::run();                 // 5 wall
        CategorySeeder::run();              // 6 category
        UserAndWallSeeder::run();           // 7 user and wall migration
        OperationAndWallSeedr::run();       // 8 operation_and_wall
        OperationAndCategorySeeder::run();  // 9 operation and category
        RuleAutoAddSeeder::run();           // 10 rule_auto_add
        /*CurrencyAndWallSeeder::run();*/


    } 
};
