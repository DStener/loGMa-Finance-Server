#include "Framework.h"

using namespace isce;


Framework::framework_t isce::app() {
	static std::once_flag flag;
	static std::shared_ptr<Framework> instance;
	std::call_once(flag, [&]() { instance.reset(new Framework()); });
	return instance;
}

void Framework::run() {	
	Route::up();
	//std::cout << _bad_request.use_count() << std::endl;

	this->server_run();
}

//framework_t Framework::bad_request(callback_t&& callback) {
//	_bad_request = callback;
//	return shared_from_this();
//}

framework_t Framework::add(route_t route) {
	_routes.push_back(std::move(route));
	return shared_from_this();
}

framework_t Framework::config(path_t path) {
	// Check, that path is exist
	if (!std::filesystem::exists(path)) { 
		return shared_from_this();
	}

	// Open config file
	std::ifstream file;
	file.open(path);

	//if (file.is_open()) {
	//	// Read entire file 
	//	std::ostringstream stream;
	//	stream << file.rdbuf();

	//	_config = json::parse(stream.str()).as_object();
	//}

	file.close();
	return shared_from_this();
}
