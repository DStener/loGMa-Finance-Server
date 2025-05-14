#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/Utils.h>
#include <isce/Model.h>

#include <isce/Route.h>

#include <isce/Framework.h>


#include "config.h"
#include "dto.h"
#include "systems/static_file.h"

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


using namespace isce;

void Migration() {

	// 0 users
	MigrationUser::up();
	UserSeeder::run();

	// 1 token
	MigrationToken::up();

	// 2 file
	MigrationFiles::up();
	FileSeeder::run();

	// 3 currency 
	MigrationСurrency::up();
	СurrencySeeder::run();

	// 4 operaion 
	MigrationOperation::up();
	OperationSeedr::run();

	// 5 wall
	MigrationWall::up();
	WallSeeder::run();

	// 6 category
	MigrationCategory::up();
	CategorySeeder::run();

	// 7 user and wall migration
	MigrationUserAndWall::up();
	UserAndWallSeeder::run();

	// 8 operation_and_wall
	MigrationOperationAndWall::up();
	OperationAndWallSeedr::run();

	// 9 operation and category
	MigrationOperationAndCategory::up();
	OperationAndCategorySeeder::run();

	// 10 rule_auto_add
	MigrationRuleAutoAdd::up();
	RuleAutoAddSeeder::run();
}

int main() {
#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif

	app()->config(CONFIG_PATH);
	app()->default_response(sys::StaticFile::finde);

	Migration();

	app()->run();

	Model::close_connection(); 
	return 0;
}