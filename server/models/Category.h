#include "isce/Model.h"


class Category : public Model {
public:
  Category(std::string table_name) : Model(table_name) {}

};

static inline std::unique_ptr<Model> category = std::make_unique<Category>("category");
 
