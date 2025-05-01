#include "auth.h"
#include "dto_auth.h"

#include <utility>

#include <boost/json/object.hpp>
#include "register.h"


void Auth::Register(const request_t& req, callback_t&& callback) {
	// Convert request json to DTO 
	auto info = DTO::fromRequest<::Register>(req);

	auto reg = Request::Register(std::move(info));
	

	
	response_t response(http::status::ok, req.version());
	response.body() = "Hello!";
	

	callback(std::move(response));
}
