#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationFiles : public Migration {
public:
	static void up()  {
		Schema::create("files", { 
			"name VARCHAR NOT NULL", 
			"description VARCHAR NULL", 
			"path  VARCHAR NOT NULL" });
	}

};



