#ifndef SERVER_TEST_H
#define SERVER_TEST_H

#include <isce/Microservice.h>

class ServerTest : isce::Microservice<ServerTest> {
public:
	//Connect methods to URL
	METHOD_LIST_BEGIN
		METHOD_ADD(ServerTest::Hello, "/test", http::verb::get)
		METHOD_ADD(ServerTest::jsonHello, "/hello_json", http::verb::get)
	METHOD_LIST_END

	// Declaring methods
	void Hello(const request_t& req, callback_t&& callback);
	void jsonHello(const request_t& req, callback_t&& callback);
};
#endif