#include "isce/Model.h"
#include "seeder.h"
#include <libpq-fe.h>
#include <isce/Framework.h>





class FileSeeder : public Seeder{
public:

  static void run() {
    
    Model::init_connection();

    std::string query = std::format("INSERT INTO files (name, description, path) VALUES ('default', 'none', '{}');",
                                    construct_path("avatar.jpg"));

    PGresult* res = PQexec(Model::get_connection(), query.c_str());
    DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK);

  }
private:
  static std::string construct_path(std::string filename) {

    const std::string relative = CMAKE_SOURCE_DIR;
    const std::string root = app()->root();

    const bool has_first_slash = relative.ends_with('/') ||
                                root.starts_with('/');
    const bool has_middle_slash = root.ends_with('/') ||
                                  filename.starts_with('/');

    return std::format("{2}{0}{3}{1}{4}",
                      (has_first_slash) ? "" : "/",
                      (has_middle_slash) ? "" : "/",
                      relative, root, filename);
  }
};