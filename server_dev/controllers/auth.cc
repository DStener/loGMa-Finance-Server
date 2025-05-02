#include "auth.h"
#include "isce/Model.h"
#include "isce/Response.h"


std::shared_ptr<response_t> Auth::registration(request_t&& request) {
	
	return response_t::Json("Data"); 
}

std::shared_ptr<response_t> Auth::login(request_t&& request) {

	return response_t::Json("Data");
}

std::shared_ptr<response_t> Auth::login2fa(request_t&& request) {

	return response_t::Json("Data");
}

std::shared_ptr<response_t> Auth::me(request_t&& request) {

	return response_t::Json("Data");
}

std::shared_ptr<response_t> Auth::out(request_t&& request) {

	return response_t::Json("Data");
}

std::shared_ptr<response_t> Auth::tokens(request_t&& request) {

	return response_t::Json("Data");;
}

std::shared_ptr<response_t> Auth::out_all(request_t&& request) {

	return response_t::Json("Data");
}