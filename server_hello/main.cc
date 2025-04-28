#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>
#include <isce/DTO.h>
#include "isce/DataBase.h"
#include <config.h>

#include "dto_server_hello.h"
#include "boost/date_time/posix_time/posix_time.hpp" 

// https://www.boost.org/doc/libs/master/doc/html/date_time.html
namespace posix_time = boost::posix_time;

using namespace isce;

int main() {
	// UserTest test{};
	// test.test = "best";

	// isce::Config::loadFile(CONFIG_PATH);
	// isce::HttpFramework::run();

	// test.test

	// auto database = new DataBase();

	// database->Insert("users", "name, age", "'Dima', 25");

	// posix_time::ptime;

	// posix_time::ptime t (posix_time::microsec_clock::local_time());
	// std::cout << posix_time::to_simple_string(t) << std::endl;

	// t += posix_time::hours(7);
	// std::cout << posix_time::to_simple_string(t) << std::endl;

}