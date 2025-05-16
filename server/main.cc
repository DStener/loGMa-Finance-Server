#include <iostream>

#include <isce/Utils.h>
#include <isce/Model.h>

#include <isce/Route.h>
#include <isce/Framework.h>

#include "config.h"
#include "dto.h"
#include "systems/static_file.h"
#include "migration/__all__.h"
#include "seeders/__all__.h"

using namespace isce;

int main() {
#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif

	std::cout << "Starting server" << std::endl;
	app()->config(CONFIG_PATH);
	app()->default_response(sys::StaticFile::finde);

	UP_ALL_MIGARTION
	RUN_ALL_SEEDERS

	app()->run();

	Model::close_connection(); 
	return 0;
}