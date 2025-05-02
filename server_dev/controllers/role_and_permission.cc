#include "controllers/role_and_permission.h"
#include "isce/Response.h"


response_t RoleAndPermission::get_permisison_role(request_t&& request) {

	return Response().json("Data");
}

response_t RoleAndPermission::add_permission_role(request_t&& request) {

	return Response().json("Data");
}

response_t RoleAndPermission::remove_permission_role(request_t&& request) {

	return Response().json("Data");
}

// response_t UserAndRole::remove_user_role(request_t&& request) {

// 	return response_t();
// }
