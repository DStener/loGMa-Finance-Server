#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

using namespace isce;

class Auth : public Controller {
public:
	/*static response_t registration(request_t&& request);*/
	static http::response<http::string_body> registration(request_t&& request);
	static http::response<http::string_body> login(request_t&& request);
	static http::response<http::string_body> login2fa(request_t&& request);
	static http::response<http::string_body> me(request_t&& request);
	static http::response<http::string_body> out(request_t&& request);
	static http::response<http::string_body> tokens(request_t&& request);
	static http::response<http::string_body> out_all(request_t&& request);
};