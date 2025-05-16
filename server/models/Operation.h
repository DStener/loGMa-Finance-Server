#include "isce/Model.h"


class Operation : public Model {
public:
  Operation(std::string table_name) : Model(table_name) {}

};
static inline std::unique_ptr<Model> operation = std::make_unique<Operation>("operation");



