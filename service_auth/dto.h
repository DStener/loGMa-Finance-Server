#pragma once

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
namespace posix_time = boost::posix_time;

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
  std::string        token;
  posix_time::ptime  id_user;
  posix_time::ptime  time;
};