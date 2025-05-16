#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationUser : public Migration {
public:
	static void up()  {
		Schema::create("users", { 
			"login VARCHAR(255) NOT NULL UNIQUE",
			"avatar INTEGER NULL", 
			"name VARCHAR(255) NOT NULL", 
			"surname  VARCHAR(255) NOT NULL", 
			"patronymic VARCHAR(255) DEFAULT NULL", 
			"birthday VARCHAR(255) NOT NULL", 
			"password VARCHAR(255) NOT NULL" });
	}

};



