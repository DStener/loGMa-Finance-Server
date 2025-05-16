#pragma once 
#include <boost/asio.hpp> 
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <memory>
#include <string>
#include <vector>

#include <isce/fields_alloc.hpp>
#include <isce/File.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace isce {
class Request {
 public:

  using boost_t = http::request<http::string_body, http::basic_fields<fields_alloc<char>>>;
  using ptr_t = std::shared_ptr<Request>;
  using var_t = std::pair<std::string, std::string>;

  Request() = delete;
  ~Request() = default;

  Request(const Request::boost_t& request, std::vector<var_t> vars)
    : _request(request), _vars(std::move(vars)) {};

  std::string input(std::string_view&& data);
  File file(std::string_view&& data);
  std::optional<std::string> cookie(std::string_view&& field);

  void shutdown();
  bool is_shutdown();
  unsigned version();
  std::string target();
 private:
   bool _is_shutdown = false;
   const Request::boost_t& _request;
   std::vector<var_t> _vars;

};
using request_t = std::shared_ptr<Request>;
} // namespace isce