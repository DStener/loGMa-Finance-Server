#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>
#include <isce/DataBase.h>
#include <isce/Microservice.h>

#include "config.h"


using namespace isce;

void route_up();


int main() {


	route_up();

	// isce::__service_name__ = PROJECT_NAME;
	// isce::Config::loadFile(CONFIG_PATH);

	// DB::get()->Create<::User>();
	// DB::get()->Create<::Token>();

	isce::HttpFramework::run();
}