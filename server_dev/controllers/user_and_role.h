#pragma once

#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h>

using namespace isce;

class UserAndRole : public Controller {
public:
	static std::shared_ptr<response_t> get_users(request_t&& request);
	static std::shared_ptr<response_t> get_user_role(request_t&& request);
	static std::shared_ptr<response_t> add_user_role(request_t&& request);
	static std::shared_ptr<response_t> remove_user_role(request_t&& request);
};