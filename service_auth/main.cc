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
#include <windows.h>

using namespace isce;

int main() {

#ifdef _WIN32
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
#endif


	app()->config(CONFIG_PATH);
	
	// MigrationUser::up();
	// UserSeeder::run();
	MigrationWall::up();



	app()->run();


	Model::close_connection(); 
	return 0;
}