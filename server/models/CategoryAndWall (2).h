#pragma once

#include "isce/Model.h"

class CategoryAndWall : public Model {
public:
  CategoryAndWall(std::string table_name) : Model(table_name) {}

};
static inline std::unique_ptr<Model> rule_auto_add = std::make_unique<CategoryAndWall>("rule_auto_add");




