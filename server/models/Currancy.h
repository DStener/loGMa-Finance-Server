#include "isce/Model.h"


class Currancy : public Model {
public:
  Currancy(std::string table_name) : Model(table_name) {}

};

static inline std::unique_ptr<Model> currancy = std::make_unique<Currancy>("currency");
 
