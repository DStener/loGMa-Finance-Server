#include <file.h>

#include <isce/Framework.h>

#include "systems/login.h"


inline std::string construct_path(std::string filename) {

  const std::string relative = CMAKE_SOURCE_DIR;
  const std::string upload = app()->upload();

  const bool has_first_slash = relative.ends_with('/') ||
    upload.starts_with('/');
  const bool has_middle_slash = upload.ends_with('/') ||
    filename.starts_with('/');

  const auto index_path = std::format("{2}{0}{3}{1}{4}",
    (has_first_slash) ? "" : "/",
    (has_middle_slash) ? "" : "/",
    relative, upload, "/index.html");

  return std::format("{2}{0}{3}{1}{4}",
                     (has_first_slash) ? "" : "/",
                     (has_middle_slash) ? "" : "/",
                     relative, upload, filename);
}


response_t FileController::get(request_t request) {

  return response()->not_found("NOT FOUND");
}


response_t FileController::upload(request_t request) {

  const auto login = sys::Login(request);
  LOGIN_CHECK_ERROR(login)

  const auto upload_file = request->file("file");
  const auto upload_path = construct_path(upload_file.filename());

  upload_file.save()


  return response()->not_found("NOT FOUND");
}