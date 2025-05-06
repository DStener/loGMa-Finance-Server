#pragma once 
#include <boost/asio.hpp> 
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <memory>
#include <string>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace isce {
class Request {
 public:
  using boost_t = http::request<http::string_body>;
  using ptr_t = std::shared_ptr<Request>;
  using var_t = std::pair<std::string, std::string>;

  Request() = default;
  ~Request() = default;
  Request(Request::boost_t&& request, std::vector<var_t> vars) 
    : _request(std::move(request)), _vars(std::move(vars)) {};

  std::string input(std::string_view&& data);
  void shutdown();
  bool is_shutdown();
  unsigned version();
 private:
   bool _is_shutdown = false;
   Request::boost_t _request;
   std::vector<var_t> _vars;

};
using request_t = std::shared_ptr<Request>;
request_t request();
} // namespace isce