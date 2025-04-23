#include <iostream>
#include <config.h>

#include <isce/Microservice.h>
#include <isce/Configure.h>

class Test : isce::Microservice<Test> {
	public:
		METHOD_LIST_BEGIN
			METHOD_ADD(Test::Hello, "/hello", http::verb::get)
			METHOD_ADD(Test::jsonHello, "/hello_json", http::verb::get)
		METHOD_LIST_END

		static void Hello(const request_t& req, callback_t&& callback) {

			/* ... */

			// Create response
			response_t response(http::status::ok, req.version());
			response.body() = "Hello!";

			callback(std::move(response));
		}

		static void jsonHello(const request_t& req, callback_t&& callback) {

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
};

int main() {
	isce::loadConfigFile(CONFIG_PATH);
	isce::HttpFramework::run();
}