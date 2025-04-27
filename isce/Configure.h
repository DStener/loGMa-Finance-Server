#ifndef ISCE_CONFIGURE_H_
#define ISCE_CONFIGURE_H_

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
		inline static json::object config;

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
};
using Config = Configure;
} // namespace isce
#endif // ISCE_CONFIGURE_H_