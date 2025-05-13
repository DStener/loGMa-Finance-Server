#pragma once

#include "isce/Model.h"

class User : public Model {
public:
  User(std::string table_name) : Model(table_name) {} 

};
static inline std::unique_ptr<Model> user = std::make_unique<User>("users");




