#pragma once 

#include <boost/asio/ip/address.hpp>
#include <memory>
#include <filesystem>

#include <boost/json.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <isce/Request.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace json = boost::json;

namespace isce {
  class  RouteObjet;
class Framework : public std::enable_shared_from_this<Framework> {
public:
  using path_t = std::filesystem::path;
  using framework_t = std::shared_ptr<Framework>;
  using route_t = std::shared_ptr<RouteObjet>;
  using routes_t = std::vector<std::shared_ptr<RouteObjet>>;
  using callback_t = std::function<response_t(request_t)>;

  void run();
  framework_t add(route_t route);
  framework_t config(path_t path);
  framework_t default_response(callback_t&& callback);

  net::ip::address address();
  unsigned short port();
  size_t workers();
  std::string root();
  std::string upload();

  json::object database();
  
private:

  route_t get_route(std::string_view&& uri, http::verb&& method);
};
Framework::framework_t app();
}