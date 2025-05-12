#include <isce/Response.h>
#include <sstream>

using namespace isce;


http::message_generator Response::make(bool keep_alive) {
  // file_body_t
  if (std::holds_alternative<file_body_t>(_response)) {

    auto resp = std::move(std::get<file_body_t>(_response));
    resp.keep_alive(keep_alive);

    return http::message_generator(std::move(resp));
  }
  
  // string_body_t
  auto resp = std::move(std::get<string_body_t>(_response));
  resp.keep_alive(keep_alive);

  return http::message_generator(std::move(resp));
}

Response::ptr_t Response::json(const json::value& data) {

  Response::string_body_t resp{ http::status::ok, 11 };
  resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  resp.set(http::field::content_type, "application/json");
  resp.body() = json::serialize(data);

  _response.emplace<Response::string_body_t>(std::move(resp));

  return shared_from_this();
}

Response::ptr_t Response::json(std::string_view&& data) {
  json::value json_data = {{"message", data}};
  return Response::json(json_data);
}

Response::ptr_t Response::file(std::string_view path) {

  beast::error_code ec;
  http::file_body::value_type body;

  body.open(path.data(), beast::file_mode::read, ec);

  // Handle the case where the file doesn't exist
  if (ec == beast::errc::no_such_file_or_directory) { 
    std::cout << "NO FILE" << std::endl;
    return not_found(std::move(path));
  }
  // Handle an unknown error
  if (ec) { 
    std::cout << path << "ERROR" << ec << std::endl;
    return shared_from_this();
  }

  auto const size = body.size();

  Response::file_body_t resp{std::piecewise_construct,
                             std::make_tuple(std::move(body)),
                             std::make_tuple(http::status::ok, 11) };
  resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  resp.set(http::field::content_type, "application/octet-stream");
  resp.content_length(size);

  _response.emplace<Response::file_body_t>(std::move(resp));

  return shared_from_this();
}   


Response::ptr_t Response::not_found(std::string_view&& target) {

  Response::string_body_t resp{ http::status::not_found, 11 };
  resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  resp.set(http::field::content_type, "text/html");
  resp.body() = std::format("The resource \"{}\" was not found.", target);

  _response.emplace<Response::string_body_t>(std::move(resp));

  return shared_from_this();
}

Response::ptr_t Response::set_status(http::status&& status) {
  /*result.result(std::move(status));*/

  return shared_from_this();
}

Response::ptr_t Response::cookie(const std::string& target,
                                 std::string path,
                                 posix_time::time_duration period) {

  const auto* facet = new posix_time::time_facet("%a, %d %b %Y %H:%M:%S GMT");
  const auto time = posix_time::microsec_clock::local_time() + period;
  
  std::stringstream ss;
  ss.imbue(std::locale(ss.getloc(), facet));
  ss << time;

  auto cookie = std::format("{}; Path={}; Expires={};",
                            target, path, ss.str());

  if (std::holds_alternative<file_body_t>(_response)) {

    auto resp = std::move(std::get<file_body_t>(_response));
    resp.set(http::field::set_cookie, cookie);
    resp.set(http::field::access_control_allow_credentials, "true");
    resp.set(http::field::access_control_expose_headers, "Set-Cookie");
    resp.set(http::field::access_control_allow_origin, "http://127.0.0.1:5555");

    _response.emplace<file_body_t>(std::move(resp));
  }
  else if (std::holds_alternative<string_body_t>(_response)) {

    auto resp = std::move(std::get<string_body_t>(_response));
    resp.set(http::field::date, "Mon, 12 May 2025 10:19:45 GMT");
    resp.set(http::field::access_control_allow_credentials, "true");
    resp.set(http::field::access_control_expose_headers, "Set-Cookie");
    resp.set(http::field::set_cookie, cookie);

    _response.emplace<string_body_t>(std::move(resp));
  }
  return shared_from_this();
}