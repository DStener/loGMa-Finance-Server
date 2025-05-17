#include <isce/Request.h>

#include <boost/url.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/regex.h>
#include <boost/algorithm/string/regex.hpp>
#include <boost/bind/bind.hpp>

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

  std::cout << target << " - " << data << std::endl;

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

// name, data, filename
inline File form_parser(std::string_view target, std::string_view&& data,
                          std::string_view&& boundary, bool is_file = false) {

  const auto separator = std::format("--{}", boundary);

  for (size_t pos = 0; pos != data.npos;) {
    
    pos += separator.size();

    const bool is_end = ("--" == std::string_view(data.begin() + pos, data.begin() + pos + 2));
    if (is_end) { break; }

    // Start position of "Content-Disposition..."
    auto __nline_pos = data.find("\n", pos + 4); // 4 = len("--") + len("\n") + 1

    // name
    const auto __name_spos = data.find("name=\"", pos);
    const auto __name_epos = data.find("\";", __name_spos);

    const bool __name_efinde = (__name_epos != data.npos);

    const auto __name_sit = data.begin() + __name_spos + 6;
    const auto __name_eit = (__name_efinde)? data.begin() + __name_epos : data.begin() + __nline_pos - 2;

    auto name = std::string(__name_sit, __name_eit);

    // filename
    const auto __filename_spos = data.find("filename=\"", pos);

    const bool __name_sfinde = (__filename_spos < __nline_pos);

    const auto __filename_sit = (__name_sfinde)? data.begin() + __filename_spos : data.begin() + __nline_pos;
    const auto __filename_eit = data.begin() + __nline_pos;

    auto filename = std::string(__filename_sit, __filename_eit);

    //std::cout << "FILENAME: " << filename << std::endl;

    // pos++
    pos = data.find(separator, pos + 1);
    if (name != target) { continue; }

    // data
    const bool has_another_line = (std::string_view(__filename_eit + 1, __filename_eit + 13) == "Content-Type");
    if (has_another_line) { __nline_pos = data.find('\n', __nline_pos + 1); }

    auto body = std::string(data.begin() + __nline_pos + 3, data.begin() + pos - 1);

    return File(std::move(name), std::move(body), std::move(filename)); 
  }
  return File("", "", "");
}

File Request::file(std::string_view&& data) {

  const auto type_it = _request.find(http::field::content_type);
  const bool has_content_type = (type_it != _request.end());

  const bool is_form_data = has_content_type &&
                            type_it->value().starts_with("multipart/form-data") ||
                            type_it->value().starts_with("application/x-www-form-urlencoded");

  if (!is_form_data) { return File(); }

  const auto value = type_it->value();

  const auto start_pos = value.find("boundary=");
  if (start_pos == value.npos) { return{}; }

  const auto start_it = value.begin() + start_pos + 9;
  std::string_view boundary(start_it, value.end());

  return form_parser(data, _request.body(), std::move(boundary));
}

std::string Request::input(std::string_view&& data) {
  
  const auto type_it = _request.find(http::field::content_type);
  const bool has_content_type = (type_it != _request.end());
  
  const bool is_form_data = has_content_type &&
                            type_it->value().starts_with("multipart/form-data") ||
                            type_it->value().starts_with("application/x-www-form-urlencoded");
  

  // [ 1 VARIANT ] : Finde in target path as regex var. Like "/test/{id}"
  for(const auto test: _vars) {
    
  }
  auto it = std::find_if(_vars.begin(), _vars.end(), [&](const var_t& var) {
    return var.first == data; });
  if (it != _vars.end()) { return std::get<1>(*it); }

  // [ 2 VARIANT ] : Finde in path var. Like "/test?id=..."
  auto out = data_parse(data, urls::url_view(_request.target()).query());
  if (!out.empty()) { return out; }


  // [ 3 VARIANT ] : Finde in request body, "form data"
  if (is_form_data) {

    const auto value = type_it->value();

    const auto start_pos = value.find("boundary=");
    if (start_pos == value.npos) { return{}; }

    const auto start_it = value.begin() + start_pos + 9;
    std::string_view boundary(start_it, value.end());

    const auto file = form_parser(data, _request.body(), std::move(boundary));
   
    return std::string{ file.data() };
  }
 
  // [ 4 VARIANT ] : Finde in request body. Like "id=...&test=..."
  out = data_parse(data, _request.body());
  if (!out.empty()) { return out; }
 
  return {};
}

std::optional<std::string> Request::cookie(std::string_view&& field) {

  const auto cookie = _request[http::field::cookie];
  if (cookie.empty()) { return {}; }

  for (size_t n = 0; n != cookie.npos; n = cookie.find(';', n)) {

    const auto next_pos = cookie.find(';', n + 1);

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