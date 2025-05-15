#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

#include "dto.h"

using namespace isce;

class FileController : public Controller {
public:
	static response_t get(request_t request);
	static response_t upload(request_t request);
};