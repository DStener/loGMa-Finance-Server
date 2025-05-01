#pragma once
#include <boost/beast/http.hpp>
#include <boost/json.hpp>

namespace http = boost::beast::http;
namespace json = boost::json;


namespace isce {
  class Response {
  public:
    static http::response<http::string_body> Json(const std::string& data) {

      http::response<http::string_body> result;

      if (data.size() < 1) {
        result.result(http::status::bad_request);
        return result;
      }

      json::value json_data = {
        {"message", data}
      };


      result.result(http::status::ok); 
      result.body() = serialize(json_data); 

      return result;
    }


  };
using response_t = Response;

} // namespace isce