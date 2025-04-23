#pragma once

#include <boost/json/src.hpp>

#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
namespace json = boost::json;

namespace isce {
namespace Configure {
	static json::object config;

	static bool loadConfigFile(fs::path path) {
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
} // namespace	Configure
namespace Config = Configure;
using namespace Configure;
} // namespace isce