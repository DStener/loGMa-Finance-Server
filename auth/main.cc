#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>
#include <isce/DataBase.h>

#include "config.h"
#include "dto_auth.h"

using namespace isce;

int main() {
	DB::get()->Create<::User>();

	isce::Config::loadFile(CONFIG_PATH);
	isce::HttpFramework::run();

	// test.test

	// auto database = new DataBase();

	// database->Insert("users", "name, age", "'Dima', 25");
}