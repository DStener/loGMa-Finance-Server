#include "auth.h"
#include "isce/Model.h"
#include "isce/Response.h"



http::response<http::string_body> Auth::registration(request_t&& request) {
	
	return response_t::Json("Data"); 
}

http::response<http::string_body> Auth::login(request_t&& request) {

	return response_t::Json("Data");
}

http::response<http::string_body> Auth::login2fa(request_t&& request) {

	return response_t::Json("Data");
}

http::response<http::string_body> Auth::me(request_t&& request) {
	return response_t::Json("Data");
}

http::response<http::string_body> Auth::out(request_t&& request) {
	return response_t::Json("Data");
}

http::response<http::string_body> Auth::tokens(request_t&& request) {
	return response_t::Json("Data");;
}

http::response<http::string_body> Auth::out_all(request_t&& request) {
	return response_t::Json("Data");
}