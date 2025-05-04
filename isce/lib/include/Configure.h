#pragma once

#include <boost/json/object.hpp>
#include <optional>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <memory>

#include <boost/json.hpp>

namespace fs = std::filesystem;
namespace json = boost::json;

namespace isce {
class Configure {
public:
	bool loadFile(fs::path path);
	std::optional<json::object> getDBConfig();
private:
	json::object _config;
};
using configure_t = std::shared_ptr<Configure>;
configure_t config();
} // namespace isce