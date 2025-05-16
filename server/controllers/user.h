#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

// #include "systems/login.h"
#include "dto.h"


using namespace isce;

class UserCNT : public Controller {
public:
	static response_t avatar(request_t request);
	static response_t update(request_t request);
};