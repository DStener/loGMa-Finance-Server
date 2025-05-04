#include "controllers/permission.h"
#include "isce/Response.h"


response_t Permission::get(request_t&& request) {

	return response()->json("Data");
}

response_t Permission::get_list(request_t&& request) {

	return response()->json("Data");
}

response_t Permission::create(request_t&& request) {

	return response()->json("Data");
}

response_t Permission::update(request_t&& request) {

	return response()->json("Data");
}

response_t Permission::delete_(request_t&& request) {

	return response()->json("Data");;
}

response_t Permission::soft_delete(request_t&& request) {

	return response()->json("Data");
}

response_t Permission::restore(request_t&& request) {

	return response()->json("Data");
}