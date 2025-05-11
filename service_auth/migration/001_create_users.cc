#include <isce/Schema.h>
#include "Migration.h"



class MigrationUser : public Migration {
public:
	void up() override {
		Schema::create("users", { "login", "name", "surname", "patronymic", "birthday", "password" });
	}

};



