#pragma once
#include <boost/beast/http.hpp>
#include <boost/json.hpp>
#include <memory>
#include <utility>
#include <filesystem>
#include <string_view>
#include <iostream>
#include <type_traits>

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


namespace http = boost::beast::http;
namespace json = boost::json;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace json = boost::json;

namespace isce {
class Response : public std::enable_shared_from_this<Response> {
public:
  using ptr_t = std::shared_ptr<Response>;
  using file_body_t = http::response<http::file_body>;
  using string_body_t = http::response<http::string_body>;
  using boost_variant_t = std::variant<string_body_t, file_body_t>;

  ~Response() = default;

  Response::ptr_t json(const json::value& data);
  Response::ptr_t json(std::string_view&& data);

  Response::ptr_t file(std::string_view path);

  Response::ptr_t not_found(std::string_view&& target);

  Response::ptr_t set_status(http::status&& status);

  http::message_generator make(bool keep_alive);

private:
  Response::boost_variant_t _response;

  Response() = default;

  friend std::shared_ptr<Response> response();
};

using response_t = std::shared_ptr<Response>;
static response_t response() { return response_t(new Response()); }
} // namespace isce