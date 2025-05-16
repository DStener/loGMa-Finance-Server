#include "Framework.h"
#include <boost/asio/ip/address.hpp>
#include <stdexcept>
#include <string>

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
		throw std::runtime_error("[!] FILE NOT EXISTS");
	}

	// Open config file
	std::ifstream file;
	file.open(path);

	if (file.is_open()) {
		// Read entire file 
		std::ostringstream stream;
		stream << file.rdbuf();

		_config = json::parse(stream.str()).as_object();
	}

	file.close();
	return shared_from_this();
}

framework_t Framework::default_response(callback_t&& callback) {
	_default_request = route_t(new RouteObjet(std::move(callback)));
	return shared_from_this();
}



net::ip::address Framework::address() {
	const auto it = _config.find("address");

	if(it == _config.end()) {
		throw std::runtime_error("In config file not found 'address'");
	}

	return net::ip::make_address(it->value().as_string());
}

unsigned short Framework::port() {
	const auto it = _config.find("port");

	if(it == _config.end()) {
		throw std::runtime_error("In config file not found 'port'");
	}

	return it->value().as_int64();
}

size_t Framework::workers() {
	const auto it = _config.find("workers");

	if(it == _config.end()) {
		throw std::runtime_error("In config file not found 'port'");
	}

	return it->value().as_int64();
}

std::string Framework::root() {
	const auto it = _config.find("root");

	if (it == _config.end()) {
		throw std::runtime_error("In config file not found 'root'");
	}

	return it->value().as_string().c_str();
}

std::string Framework::upload() {
	const auto it = _config.find("upload_path");

	if (it == _config.end()) {
		throw std::runtime_error("In config file not found 'root'");
	}

	return it->value().as_string().c_str();
}

json::object Framework::database() {
	const auto it = _config.find("database");

	if (it == _config.end()) {
		throw std::runtime_error("In config file not found 'database'");
	}

	return it->value().as_object();
}
