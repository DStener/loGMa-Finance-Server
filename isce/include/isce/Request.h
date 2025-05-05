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
  void input(std::string& data);
  void shutdown();
  bool is_shutdown();
 private:
   bool _is_shutdown = false;
};
using request_t = std::shared_ptr<Request>;
request_t request();
} // namespace isce