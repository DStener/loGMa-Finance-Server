#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationOperation : public Migration {
public:
	static void up() {
		Schema::create("operation", {
			"value BIGINT NOT NULL",
			"description VARCHAR NULL",
			"id_currency INTEGER NULL",
			"id_user INTEGER NULL",
			"time TIMESTAMP DEFAULT NOW()"
			});
	}
};



