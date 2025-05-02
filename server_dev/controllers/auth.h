#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

using namespace isce;

class Auth : public Controller {
public:
	/*static response_t registration(request_t&& request);*/
	static response_t registration(request_t&& request);
	static response_t login(request_t&& request);
	static response_t login2fa(request_t&& request);
	static response_t me(request_t&& request);
	static response_t out(request_t&& request);
	static response_t tokens(request_t&& request);
	static response_t out_all(request_t&& request);
};