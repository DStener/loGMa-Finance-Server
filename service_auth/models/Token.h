#pragma once 

#include "isce/Model.h"

class Token : public Model {
public:
  Token(std::string table_name) : Model(table_name) {} 

};
static inline std::unique_ptr<Model> token = std::make_unique<Token>("token");



