#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>

#include <isce/DataBase.h>
#include <isce/Utils.h>

#include <isce/Route.h>

#include <isce/Framework.h>

#include "config.h"

using namespace isce;

int main() {

	app()->config(CONFIG_PATH);
	app()->run();

	return 0;
}