#include <iostream>
#include <config.h>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>

int main() {
	isce::loadConfigFile(CONFIG_PATH);
	isce::HttpFramework::run();
}