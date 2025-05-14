#include "isce/Model.h"


class FileModel : public Model {
public:
  FileModel(std::string table_name) : Model(table_name) {}

};

static inline std::unique_ptr<FileModel> file = std::make_unique<FileModel>("files");




