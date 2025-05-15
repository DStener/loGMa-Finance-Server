#pragma once

#include "isce/Model.h"

class UserAndWall : public Model {
public:
  UserAndWall(std::string table_name) : Model(table_name) {}

};
static inline std::unique_ptr<Model> user_and_wall = std::make_unique<UserAndWall>("user_and_wall");




