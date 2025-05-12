#pragma once

#include <string>

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