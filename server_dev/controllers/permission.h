#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

using namespace isce;

class Permission : public Controller {
public:
	static response_t get(request_t request);
	static response_t get_list(request_t request);
	static response_t create(request_t request);
	static response_t update(request_t request);
	static response_t delete_(request_t request);
	static response_t soft_delete(request_t request);
	static response_t restore(request_t request);
};