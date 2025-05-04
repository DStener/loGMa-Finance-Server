#pragma once 
#include <boost/asio.hpp> 
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace isce {
class Request {
public:
  static void input(std::string& data) {
    
  }
};
using request_t = Request;
} // namespace isce