#pragma once

#include <boost/json/serialize.hpp>
#include <isce/Request.h>

#include "models/User.h"
#include "models/Token.h"
#include "dto.h"

using namespace isce;

#define LOGIN_CHECK_ERROR(obj)                \
if (!obj.message.empty()) {                   \
  return response()->json(obj.message)        \
    ->set_status(http::status::unauthorized); \
}

namespace sys {
class Login {
public:

  size_t id = 0;
  size_t id_token = 0;
  RegisterDTO user;

  std::string message;

  Login(request_t request) {

    message = "Not authorized";

    const auto condition = std::format("token = '{}'", request->cookie("token").value_or(""));
    const auto token_vec = token->find<TokenDTO>(condition);

    // Return error
    if (token_vec.size() == 0) { return; }

    id_token = token_vec[0].first;
    const auto user_vec = ::user->find<RegisterDTO>(std::format("id = {}", token_vec[0].second.id_user));

    // Return error
    if (user_vec.size() == 0) { return;}

    id = user_vec[0].first;
    user = std::move(user_vec[0].second);
    message = "";
  }

  Login(const std::string& login, const std::string& password) {

    message = "Invalid username or password";

    const auto condition = std::format("login = '{}' AND password = '{}'",
                                                          login, password);

    auto user_vec = ::user->find<RegisterDTO>(condition);

    // Return error
    if (user_vec.size() == 0) { return; }

    id = user_vec[0].first;
    user = std::move(user_vec[0].second);
    message = "";
  }


  ~Login() = default;
};
} // namespace system