#include <boost/json/object.hpp>
#include <file.h>

#include <format>
#include <isce/Framework.h>
#include <string>

#include "dto.h"
#include "systems/login.h"
#include "models/file.h"


inline std::string construct_path(std::string filename) {

  const std::string relative = CMAKE_SOURCE_DIR;
  const std::string upload = app()->upload();

  const bool has_first_slash = relative.ends_with('/') ||
                               upload.starts_with('/');
  const bool has_middle_slash = upload.ends_with('/') ||
                                filename.starts_with('/');

  return std::format("{2}{0}{3}{1}{4}",
                     (has_first_slash) ? "" : "/",
                     (has_middle_slash) ? "" : "/",
                     relative, upload, filename);
}

response_t FileController::get(request_t request) {

  const auto id = request->input("id");
  if(id.empty()) { return response()->not_found("NOT FOUND"); }

  const auto file_vec= file->find<FileDTO>(std::format("id = {}", id));
  if(file_vec.empty()) { return response()->not_found("NOT FOUND"); }

  return response()->file(file_vec[0].second.path);
}


response_t FileController::upload(request_t request) {

  const auto login = sys::Login(request);
  LOGIN_CHECK_ERROR(login)

  const auto upload_file = request->file("file");
  const std::string upload_path = construct_path(upload_file.filename());

  upload_file.save(upload_path);

  FileDTO dto_file  {
    std::string{upload_file.name()},
    "",
    upload_path,
  };

  json::object json;
  json["id"] = std::to_string(file->create<FileDTO>(dto_file));

  return response()->json(json);
}