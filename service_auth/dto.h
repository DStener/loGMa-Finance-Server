#pragma once

#include <string>

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