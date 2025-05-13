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


struct CreateDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

struct CreateCategoryDTO {
  std::string icon;
  std::string name;
  std::string id_wall;
};

struct UpdateCategoryDTO {
  std::string icon;
  std::string name;
  std::string id_wall;
};

struct UpdateDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

struct conditionsDTO {
  std::string id;
};


struct GetDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

