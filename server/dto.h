#pragma once

#include <isce/DTO.h>

#include <boost/date_time/posix_time/posix_time.hpp>
namespace posix_time = boost::posix_time;

using namespace isce;

// operation
struct OperationCreateDTO {
  std::string value;
  std::string id_currency;
  std::string id_user;
};

// bank

struct BankRequestDTO {
  std::string iso;
  std::string date;
};


struct OperationUpdateDTO {
  std::string value;
  std::string id_currency;
  std::string id_user;
};


struct LoginDTO {
  std::string login;
  std::string password;
};

struct RegisterDTO {
  std::string login;
  std::string avatar;
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

// operation and wall
struct OperationAndWallDTO {
  std::string id_wall;
};

// category and wall
struct CategoryAndWallDTO {
  std::string id_wall;
};


// add user to wall

struct UserToWallDTO {
  std::string id_user;
  std::string id_wall;
  std::string is_admin;
};
struct GetUserWall {
  std::string id_user;
};

// wall
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

struct FileDTO {
  std::string name;
  std::string description;
  std::string path;
};
