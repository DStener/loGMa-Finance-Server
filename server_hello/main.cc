#include <iostream>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>
#include "isce/DataBase.h"
#include <config.h>


using namespace isce;

int main() {
	isce::Config::loadFile(CONFIG_PATH);
	isce::HttpFramework::run();
	auto db = isce::DB::get();

	


	

}