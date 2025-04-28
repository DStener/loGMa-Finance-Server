#include "auth.h"
#include "dto_auth.h"

#include <boost/json/object.hpp>
#include <string_view>
#include <utility>

void Auth::Register(const request_t& req, callback_t&& callback) {
	// Convert request json to DTO 
	auto reg = DTO::fromRequest<::Register>(req);
	// json::object json = DTO::toJson(reg);

	

	// std::cout << reg.username << std::endl;
	// std::cout << json::serialize(json) << std::endl;
	
	response_t response(http::status::ok, req.version());
	response.body() = "Hello!";

	callback(std::move(response));
}
