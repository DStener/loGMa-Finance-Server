#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

#include "dto.h"

using namespace isce;

class Bank : public Controller {
public:
	static response_t get_rate(request_t request);
};