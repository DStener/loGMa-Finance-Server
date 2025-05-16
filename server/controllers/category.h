#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

#include "dto.h"

using namespace isce;

class CategoryController : public Controller {
public:
	static response_t create(request_t request);
	static response_t update(request_t request);
	static response_t get(request_t request);
	static response_t delete_(request_t request);
	static response_t set_limit(request_t request);
};