#pragma once
#include <boost/beast/http.hpp>
#include <boost/json.hpp>
#include <memory>
#include <utility>


namespace http = boost::beast::http;
namespace json = boost::json;


namespace isce {
class Response : public std::enable_shared_from_this<Response> {
public:
  ~Response() = default;


  auto json(const json::value& data) {

    result.result(http::status::ok); 
    result.body() = serialize(data); 

    return shared_from_this();
  }

  auto json(std::string_view&& data) {
    json::value json_data = {
      {"message", data}
    };

    result.result(http::status::ok);
    result.body() = serialize(json_data);

    return shared_from_this();
  }

  auto not_found() {
    result.result(http::status::not_found);
    return shared_from_this();
  }

  auto make() {
    return result;
  }

  auto set_status(http::status&& status) {
    result.result(std::move(status));
      
    return shared_from_this();
  }

private:
  http::response<http::string_body> result;

  Response() = default;

  friend std::shared_ptr<Response> response();
};

using response_t = std::shared_ptr<Response>;
static response_t response() { return response_t(new Response()); }
} // namespace isce