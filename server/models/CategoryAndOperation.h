#pragma once

#include "isce/Model.h"

class OperationAndCategory : public Model {
public:
  OperationAndCategory(std::string table_name) : Model(table_name) {}

};
static inline std::unique_ptr<Model> operation_and_category = std::make_unique<CategoryAndWall>("operation_and_category");




