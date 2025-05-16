#pragma once

#include "user_migration.h"
#include "token_migration.h"
#include "migration/user_and_wall_migration.h"
#include "migration/operation_migration.h"
#include "migration/category_migration.h"
#include "migration/operation_and_wall_migration.h"
#include "migration/currency_migration.h"
#include "migration/rule_auto_add_migration.h"
#include "migration/operation_and_category_migration.h"
#include "migration/wall_migraion.h"
#include "migration/file_migration.h"
//#include "migration/currency_and_wall_migration.h"

#define UP_ALL_MIGARTION AllMigration::up();

class AllMigration {
public:
    static void up() {
        
        MigrationUser::up();                    // 0 users
        MigrationToken::up();                   // 1 token
        MigrationFiles::up();                   // 2 file
        MigrationCurrency::up();                // 3 currency 
        MigrationOperation::up();               // 4 operaion 
        MigrationWall::up();                    // 5 wall
        MigrationCategory::up();                // 6 category
        MigrationUserAndWall::up();             // 7 user and wall migration
        MigrationOperationAndWall::up();        // 8 operation_and_wall
        MigrationOperationAndCategory::up();    // 9 operation and category
        MigrationRuleAutoAdd::up();             // 10 rule_auto_add
        //MigrationCurrencyAndWall::up();         // 11 currency_and_wall
    }
};