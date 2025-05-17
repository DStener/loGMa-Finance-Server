#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationWall : public Migration {
public:
	static void up() {
		Schema::create("wall", {
			"name VARCHAR(255) NOT NULL",
			"is_group BOOLEAN DEFAULT false",
			"is_public BOOLEAN DEFAULT false",
			"lim BIGINT NOT NULL", // sum(all operation wall) && sum()
			"default_currancy VARCHAR(3) DEFAULT 'RUB'"
			});
	}

};



