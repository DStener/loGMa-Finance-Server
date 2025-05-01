#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

using namespace isce;

class RoleAndPermission : public Controller {
public:
	static response_t get_permisison_role(request_t&& request);
	static response_t add_permission_role(request_t&& request);
	static response_t remove_permission_role(request_t&& request);
};