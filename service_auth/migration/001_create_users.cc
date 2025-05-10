#include <isce/Schema.h>




class Migration {
public:
  void up() {
    Schema::create("users", {"name varchar(255)", "email varchar(255)", "age integer"});
  }

};



