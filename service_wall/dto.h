#pragma once

#include <string>

struct CreateDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

struct UpdateDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

struct DeleteDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};

struct GetDTO {
  std::string name;
  std::string is_group;
  std::string is_public;
};