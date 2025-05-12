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

#include "user_migration.h"
#include "users_seeder.h"
#include "token_migration.h"

using namespace isce;

int main() {

	app()->config(CONFIG_PATH);

	MigrationUser::up();
	UserSeeder::run();

	MigrationToken::up();

	app()->run();

	Model::close_connection(); 
	return 0;
}