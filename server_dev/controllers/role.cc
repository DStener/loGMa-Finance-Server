#include "controllers/role.h"
#include "isce/Response.h"
#include <iostream>

response_t Role::get(request_t request) {
	
	return response()->json("Data");
}

response_t Role::get_list(request_t request) {

	return response()->json("Data");
}

response_t Role::create(request_t request) {

	return response()->json("Data");
}

response_t Role::update(request_t request) {

	return response()->json("Data");
}

response_t Role::delete_(request_t request) {

	return response()->json("Data");
}

response_t Role::soft_delete(request_t request) {

	return response()->json("Data");
}

response_t Role::restore(request_t request) {

	return response()->json("Data");
}