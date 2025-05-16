#pragma once 

#include <isce/Framework.h>
#include <isce/Controller.h>
#include <isce/Request.h>
#include <isce/Response.h> 

#include "config.h"

using namespace isce;

namespace sys {
class StaticFile {
public:
  StaticFile() = delete;
  ~StaticFile() = delete;

  static response_t finde(request_t request) {

    const std::string relative = CMAKE_SOURCE_DIR;
    const std::string root = app()->root();
    const std::string target = request->target();

    const bool has_first_slash = relative.ends_with('/') ||
                                 root.starts_with('/');
    const bool has_middle_slash = root.ends_with('/') ||
                                  target.starts_with('/');

    const auto index_path = std::format("{2}{0}{3}{1}{4}",
                                        (has_first_slash) ? "" : "/",
                                        (has_middle_slash) ? "" : "/",
                                        relative, root, "/index.html");

    const auto path = std::format("{2}{0}{3}{1}{4}",
                                  (has_first_slash)? "" : "/",
                                  (has_middle_slash)? "" : "/",
                                  relative, root, target);

    if (!std::filesystem::exists(path) || target.empty() || target == "/") {
      return response()->file(index_path)
                       ->mime("text/html")
                       ->set_status(http::status::not_found);
    }

    return response()->file(path)
                     ->mime(mime_type(target));
  }

  static std::string mime_type(const std::string& path) {
    if (path.ends_with(".htm"))  return "text/html";
    if (path.ends_with(".html")) return "text/html";
    if (path.ends_with(".php"))  return "text/html";
    if (path.ends_with(".css"))  return "text/css";
    if (path.ends_with(".txt"))  return "text/plain";
    if (path.ends_with(".js"))   return "application/javascript";
    if (path.ends_with(".json")) return "application/json";
    if (path.ends_with(".xml"))  return "application/xml";
    if (path.ends_with(".swf"))  return "application/x-shockwave-flash";
    if (path.ends_with(".flv"))  return "video/x-flv";
    if (path.ends_with(".png"))  return "image/png";
    if (path.ends_with(".jpe"))  return "image/jpeg";
    if (path.ends_with(".jpeg")) return "image/jpeg";
    if (path.ends_with(".jpg"))  return "image/jpeg";
    if (path.ends_with(".gif"))  return "image/gif";
    if (path.ends_with(".bmp"))  return "image/bmp";
    if (path.ends_with(".ico"))  return "image/vnd.microsoft.icon";
    if (path.ends_with(".tiff")) return "image/tiff";
    if (path.ends_with(".tif"))  return "image/tiff";
    if (path.ends_with(".svg"))  return "image/svg+xml";
    if (path.ends_with(".svgz")) return "image/svg+xml";
    return "application/text";
  }


};
} // namespace sys
