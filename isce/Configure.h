#pragma once

#include <boost/json/object.hpp>
#include <optional>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <boost/json.hpp>

namespace fs = std::filesystem;
namespace json = boost::json;

namespace isce {
class Configure {
 public:
	static bool loadFile(fs::path path) {
		// Check, that path is exist
		if (!fs::exists(path)) { return false; }

		// Open config file
		std::ifstream file;
		file.open(path);

		if (file.is_open()) {
			// Read entire file 
			std::ostringstream stream;
			stream << file.rdbuf();

			config = json::parse(stream.str()).as_object();
		}

		file.close();
		return true;
	}

	static std::optional<json::object> getDBConfig() {
		auto it = config.find("database");
		if(it == config.end()) { return {}; }
		return it->value().as_object();
	}

 private:
	inline static json::object config;
};
using Config = Configure;
} // namespace isce