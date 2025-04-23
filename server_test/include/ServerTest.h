//#pragma once 
//
//#include <isce/Microservice.h>
//#include <isce/HttpFramework.h>
//
//class ServerTest : isce::Microservice<ServerTest> {
//public:
//	//Connect methods to URL
//	METHOD_LIST_BEGIN
//		METHOD_ADD(ServerTest::Hello, "/hello", http::verb::get)
//		//METHOD_ADD(ServerTest::jsonHello, "/hello_json", http::verb::get)
//	METHOD_LIST_END
//
//	// Declaring methods
//	static void Hello(const request_t& req, callback_t&& callback) {
//
//		/* ... */
//
//		// Create response
//		response_t response(http::status::ok, req.version());
//		response.body() = "Hello!";
//
//		callback(std::move(response));
//	}
//	//static void jsonHello(const request_t& req, callback_t&& callback);
//};