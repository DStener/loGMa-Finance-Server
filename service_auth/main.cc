#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/DataBase.h>
#include <isce/Utils.h>
#include <isce/Model.h>

#include <isce/Route.h>

#include <isce/Framework.h>
#include "config.h"

#include "user_migration.h"
#include "users_seeder.h"
#include "token_migration.h"

using namespace isce;

int main() {

	app()->config(CONFIG_PATH);
	
<<<<<<< HEAD
	// MigrationUser::up();
	// UserSeeder::run();
	MigrationWall::up();

=======
	MigrationUser::up();
	UserSeeder::run();
>>>>>>> 868da94d1c53cbd5b39d814d554f2b9680be7607

	MigrationToken::up();

	app()->run();

	Model::close_connection(); 
	return 0;
}