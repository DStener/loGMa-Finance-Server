#include "server_hello.h"

void ServerHello::Hello(const request_t& req, callback_t&& callback) {

	/* ... */

	// Create response
	response_t response(http::status::ok, req.version());
	response.body() = "Hello!";

	callback(std::move(response));
}

void ServerHello::JsonHello(const request_t& req, callback_t&& callback) {

	/* ... */

	json::value json = {
		{"message", "Hello from JSON!!!"}
	};

	// Create response
	response_t response(http::status::ok, req.version());
	response.set(http::field::content_type, "application/json");
	response.body() = json::serialize(json);

	callback(std::move(response));
}

void ServerHello::FileHello(const request_t& req, callback_t&& callback) {

	/* ... */

	// Create response
	response_t response(http::status::ok, req.version());
	response.set("FILE", std::format("{}/hello.html", CMAKE_CURRENT_SOURCE_DIR));

	callback(std::move(response));
}