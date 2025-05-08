#include <isce/Model.h>
#include <migration/Schema.h>
#include <isce/DataBase.h>
#include "Models/Role.h"

class Role_seeder {
public:
  void run() {
    role.create("users", { "title", "description", "code" }, { "admin", "admin role", "admin" });
    
    
  }
    

private:
  Role role;

};