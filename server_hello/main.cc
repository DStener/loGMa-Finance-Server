#include <iostream>

#include <isce/Configure.h>
#include <isce/HttpFramework.h>

#include <config.h>

int main() {
	isce::Config::loadFile(CONFIG_PATH);
	isce::HttpFramework::run();
}