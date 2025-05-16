#include "Configure.h"

using namespace isce;

configure_t config() {
	static std::once_flag flag;
	static std::shared_ptr<Configure> instance;
	std::call_once(flag, [&]() { instance.reset(new Configure()); });
	return instance;
}

bool Configure::loadFile(fs::path path) {
	// Check, that path is exist
	if (!fs::exists(path)) { return false; }

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
	return true;
}

std::optional<json::object> Configure::getDBConfig() {
	auto it = _config.find("database");
	if (it == _config.end()) { return {}; }
	return it->value().as_object();
}