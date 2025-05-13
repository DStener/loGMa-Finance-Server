#include <isce/Request.h>

#include <boost/url.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>


namespace urls = boost::urls;

using namespace isce;

inline std::string data_parse(std::string_view target, std::string_view&& data) {

  const auto offset = target.size() + 1;
  const auto target_pos = data.find(std::format("{}=", target));
  const auto ampersand_pos = data.find('&', target_pos);
  const auto last_ampersand_pos = data.find_last_of('&');
  
  const bool target_found = (target_pos != std::string_view::npos);
  const bool ampersand_found = (ampersand_pos != std::string_view::npos);
  const bool last_ampersand_found = (last_ampersand_pos != std::string_view::npos);

  if (!target_found) { 
    return {}; 
  }

  if (!ampersand_found && (!last_ampersand_found || target_pos > last_ampersand_pos)) {
    return std::string(data.begin() + target_pos + offset, data.end());
  }

  if (ampersand_found) {
    return std::string(data.begin() + target_pos + offset, data.begin() + ampersand_pos);
  }

  return {};
}

std::string Request::input(std::string_view&& data) {
  
  // [ 1 VARIANT ] : Finde in target path as regex var. Like "/test/{id}"
  auto it = std::find_if(_vars.begin(), _vars.end(), [&](const var_t& var) { 
                         return var.first == data; });
  if (it != _vars.end()) { return std::get<1>(*it); }

  // [ 2 VARIANT ] : Finde in path var. Like "/test?id=..."
  auto out = data_parse(data, urls::url_view(_request.target()).query());
  if (!out.empty()) { return out; }

  // [ 3 VARIANT ] : Finde in request body. Like "id=...&test=..."
  out = data_parse(data, _request.body());
  if (!out.empty()) { return out; } 

  // [ 4 VARIANT ] : Finde in request body, "form data"s
  /* ... */

  return {};
}

std::optional<std::string> Request::cookie(std::string_view&& field) {

  const auto cookie = _request[http::field::cookie];

  for (size_t n = 0; n != cookie.npos; n = cookie.find(';', n)) {

    const auto next_pos = cookie.find(';', ++n);

    const auto next_it = ((next_pos == cookie.npos) ? cookie.end() : cookie.begin() + next_pos);
    const auto current_it = cookie.begin() + cookie.find_first_not_of(' ', n);
    
    const std::string_view part(current_it, next_it);
    const auto equal_pos = part.find('=');

    if (std::string_view(current_it, current_it + equal_pos) != field) { continue; }

    return std::string(current_it + equal_pos + 1, next_it);
  }

  return {};
}

void Request::shutdown() {
  _is_shutdown = true;
}
bool Request::is_shutdown() {
  return _is_shutdown;
}

unsigned Request::version() {
  return _request.version();
}

std::string Request::target() {
  return _request.target();
}