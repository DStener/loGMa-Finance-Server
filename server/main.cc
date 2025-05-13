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

#include "users_seeder.h"
#include "seeders/category_seeder.h"
#include "seeders/user_and_wall_seeder.h"
#include "seeders/operation_seeder.h"
#include "seeders/operation_and_wall_seeder.h"
#include "seeders/currency_seeder.h"
#include "seeders/rule_auto_add_seeder.h"

using namespace isce;

int main() {

	app()->config(CONFIG_PATH);
	app()->default_response(sys::StaticFile::finde);

	//MigrationUser::up();
	/*UserSeeder::run();*/
	/*MigrationUserAndWall::up();
	UserAndWallSeeder::run();

	MigrationOperation::up();
	OperationSeedr::run();
	MigrationToken::up();*/

	//MigrationCategory::up();
	//CategorySeeder::run();

	/*MigrationOperationAndWall::up();
	OperationAndWallSeedr::run();*/

	/*MigrationÑurrency::up();
	ÑurrencySeeder::run();*/

	/*MigrationRuleAutoAdd::up();
	RuleAutoAddSeeder::run();*/


	app()->run();

	Model::close_connection(); 
	return 0;
}