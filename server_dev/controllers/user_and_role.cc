#include "controllers/user_and_role.h"
#include "isce/Response.h"


std::shared_ptr<response_t> UserAndRole::get_users(request_t&& request) {

	return Response().json("Data");
}

std::shared_ptr<response_t> UserAndRole::get_user_role(request_t&& request) {

	return Response().json("Data");
}

std::shared_ptr<response_t>UserAndRole::add_user_role(request_t&& request) {

	return Response().json("Data");
}

std::shared_ptr<response_t> UserAndRole::remove_user_role(request_t&& request) {

	return Response().json("Data");
}
