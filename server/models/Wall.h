#include "isce/Model.h"


class Wall : public Model {
public:
  Wall(std::string table_name) : Model(table_name) {} 

};

static inline std::unique_ptr<Model> wall = std::make_unique<Wall>("wall");




