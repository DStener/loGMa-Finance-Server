#include <boost/beast/http/status.hpp>
#include <boost/json/serializer.hpp>
#include <filesystem>
#include <isce/Response.h>
#include <sstream>

using namespace isce;

extern response_t isce::response() { return response_t(new Response()); }

void Response::make_string_body(string_body_t& resp) {
  resp->result(_status);
  resp->keep_alive(false);
  resp->set(http::field::content_type, _content_type);
  resp->body() = _body;

  if(!_cookie.empty()) {
    resp->set(http::field::access_control_allow_credentials, "true");
    resp->set(http::field::access_control_expose_headers, "Set-Cookie");
    resp->set(http::field::set_cookie, _cookie);
  }

  resp->prepare_payload();
}

void Response::make_file_body(file_body_t& resp) {

  http::file_body::value_type file;
  beast::error_code ec;
  file.open(_body.c_str(),
            beast::file_mode::read,
            ec);
  if(ec)
  {
      std::cerr << ec << std::endl;
      return;
  }
 
  resp->result(http::status::ok);
  resp->keep_alive(false);
  resp->set(http::field::content_type, _content_type);
  resp->body() = std::move(file);

  // X-Content-Type-Options
  if (_content_type == "text/css") {
    resp->set("X-Content-Type-Options", "style");
  } else if (_content_type == "application/javascript"){
    resp->set("X-Content-Type-Options", "script");
  }


  if(!_cookie.empty()) {
    resp->set(http::field::access_control_allow_credentials, "true");
    resp->set(http::field::access_control_expose_headers, "Set-Cookie");
    resp->set(http::field::set_cookie, _cookie);
  }

  resp->prepare_payload();
}


Response::ptr_t Response::json_(const json::value& data) {

  json::value json = data;
  if (data.is_string()) { json = json::value{{"message", data.as_string()}}; }

  _is_file = false;
  _body = json::serialize(json);
  _content_type = "application/json";
  _status = http::status::ok;

  return shared_from_this();
}

Response::ptr_t Response::file(std::string_view path) {

  if(!std::filesystem::exists(path)) {
    std::cout << "NO FILE" << std::endl;
  }

  _is_file = true;
  _body = std::string{path};
  _content_type = "application/octet-stream";
  _status = http::status::ok;

  return shared_from_this();
}   


Response::ptr_t Response::not_found(std::string_view&& target) {

  auto json = json::value{{"message", target.data()}};

  _is_file = false;
  _body = json::serialize(json);
  _content_type = "application/json";
  _status = http::status::not_found;

  return shared_from_this();
}

Response::ptr_t Response::set_status(http::status&& status) {
  _status = std::move(status);
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

  _cookie = std::format("{}; Path={}; Expires={};",
                                    target, path, ss.str());

  return shared_from_this();
}


Response::ptr_t Response::mime(std::string&& mime) {
  _content_type = std::move(mime);
  return shared_from_this();
}