#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/json.hpp>
#include <boost/json/array.hpp>
#include <boost/json/object.hpp>
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

#include <boost/date_time/posix_time/posix_time.hpp>

#include <isce/fields_alloc.hpp>

namespace posix_time = boost::posix_time;

namespace http = boost::beast::http;
namespace json = boost::json;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace json = boost::json;

namespace isce {
class Response : public std::enable_shared_from_this<Response> {
public:
  using alloc_t = fields_alloc<char>;
  using ptr_t = std::shared_ptr<Response>;
  using file_body_t = boost::optional<http::response<http::file_body, http::basic_fields<alloc_t>>>;
  using string_body_t = boost::optional<http::response<http::string_body, http::basic_fields<alloc_t>>>;

  ~Response() = default;

  Response::ptr_t json(const json::object& data) { return std::move(json_(data)); }
  Response::ptr_t json(const json::array& data) { return std::move(json_(data)); }
  Response::ptr_t json(std::string_view&& data) { 
    json::object json {{"message", data}};
    return std::move(json_(json)); 
  }

  

  // Response::ptr_t json(std::string_view&& data);

  Response::ptr_t file(std::string_view path);
  Response::ptr_t not_found(std::string_view&& target);
  Response::ptr_t set_status(http::status&& status);
  Response::ptr_t mime(std::string&& mime);
  Response::ptr_t cookie(const std::string& target, 
                         std::string path = "/",
                         posix_time::time_duration period = posix_time::hours(90 * 24));

  // http::message_generator make(bool keep_alive);
  void make_string_body(string_body_t& resp);
  void make_file_body(file_body_t& resp);

  bool is_file_response() { return _is_file; }

  Response() = default;
private:
  // Response::boost_variant_t _response;

  Response::ptr_t json_(const json::value& data);

  bool _is_file;
  std::string _body;
  std::string _content_type;
  http::status _status;
  std::string _cookie;
  

  friend std::shared_ptr<Response> response();
};

using response_t = std::shared_ptr<Response>;
response_t response();
} // namespace isce