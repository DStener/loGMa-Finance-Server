//#include "ServerTest.h"
//
////void ServerTest::Hello(const request_t& req, callback_t&& callback) {
////
////	/* ... */
////
////	// Create response
////	response_t response(http::status::ok, req.version());
////	response.body() = "Hello!";
////
////	callback(std::move(response));
////}
//
////void ServerTest::jsonHello(const request_t& req, callback_t&& callback) {
////
////	/* ... */
////
////	json::value json = {
////		{"message", "Hello from JSON!!!"}
////	};
////
////	// Create response
////	response_t response(http::status::ok, req.version());
////	response.set(http::field::content_type, "application/json");
////	response.body() = json::serialize(json);
////
////	callback(std::move(response));
////}