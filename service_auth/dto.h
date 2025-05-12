#pragma once

#include <isce/DTO.h>

#include <boost/date_time/posix_time/posix_time.hpp>
namespace posix_time = boost::posix_time;

using namespace isce;

struct LoginDTO {
  std::string login;
  std::string password;
};

struct RegisterDTO {
  std::string login;
  std::string name;
  std::string surname;
  std::string patronymic;
  std::string birthday;
  std::string password;
};

struct TokenDTO {
  std::string token;
  std::string id_user;
  std::string time;
};

