#pragma once 
#include <boost/asio.hpp> 
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace isce {
class Request {
 public:
  using boost_t = http::request<http::string_body>;
  using ptr_t = std::shared_ptr<Request>;

  Request() = default;
  ~Request() = default;
  Request(Request::boost_t&& request) : _request(std::move(request)) {};

  void input(std::string& data);
  void shutdown();
  bool is_shutdown();
  unsigned version();
 private:
   bool _is_shutdown = false;
   Request::boost_t _request;
};
using request_t = std::shared_ptr<Request>;
request_t request();
} // namespace isce