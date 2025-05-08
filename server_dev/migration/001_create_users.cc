#include "Schema.h"
#include <libpq-fe.h>




class Migration {
  // be careful, id is already exist

public:
  void up() {
    Schema::create("users", {"name varchar(255)", "email varchar(255)", "age integer"});
  }

};



