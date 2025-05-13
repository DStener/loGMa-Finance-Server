#include <isce/Schema.h>
#include "Migration.h"



class MigrationUser : public Migration {
public:
	static void up()  {
		Schema::create("users", { 
			"login VARCHAR(255)", 
			"name VARCHAR(255)", 
			"surname  VARCHAR(255)", 
			"patronymic VARCHAR(255)", 
			"birthday VARCHAR(255)", 
			"password VARCHAR(255)" });
	}

};



