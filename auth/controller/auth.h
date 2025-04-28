#pragma once

#include <isce/Microservice.h>
#include <isce/DTO.h>

#include "config.h"
#include "dto_auth.h"

class Auth : isce::Microservice<Auth> {
public:
	//Connect methods to URL
	METHOD_LIST_BEGIN
		METHOD_ADD(Auth::Register, "/api/auth/register", http::verb::post)
	METHOD_LIST_END

	// Declaring methods
	void Register(const request_t& req, callback_t&& callback);
};