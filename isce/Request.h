#pragma once 
#include <boost/asio.hpp> 
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>


namespace beast = boost::beast;
namespace http = beast::http;


namespace isce {
class Request {
public:
  static void input(std::string& name) {
    http::request<http::string_body> req;

    if (req.method() == http::verb::post) {
      
    }

  }
};
using request_t = Request;
} // namespace isce