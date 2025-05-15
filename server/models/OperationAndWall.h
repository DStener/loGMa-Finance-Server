#pragma once

#include "isce/Model.h"

class OperationAndWall : public Model {
public:
  OperationAndWall(std::string table_name) : Model(table_name) {}

};
static inline std::unique_ptr<Model> operation_and_wall = std::make_unique<OperationAndWall>("operation_and_wall");




