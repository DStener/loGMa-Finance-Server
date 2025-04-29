#pragma once

#include <isce/Microservice.h>

#include "config.h"

class ServerHello : isce::Microservice<ServerHello> {
public:
	//Connect methods to URL
	METHOD_LIST_BEGIN
		METHOD_ADD(ServerHello::Hello, "/hello", http::verb::post)
		METHOD_ADD(ServerHello::JsonHello, "/hello_json", http::verb::get)
		METHOD_ADD(ServerHello::FileHello, "/file_json", http::verb::get)
	METHOD_LIST_END

	// Declaring methods
	void Hello(const request_t& req, callback_t&& callback);
	void JsonHello(const request_t& req, callback_t&& callback);
	void FileHello(const request_t& req, callback_t&& callback);
};