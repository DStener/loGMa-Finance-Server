#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationOperation : public Migration {
public:
	static void up() {
		Schema::create("operation", {
			"value BIGINT NOT NULL",
			"description VARCHAR DEFAULT NULL",
			"iso_currency VARCHAR(3) NOT NULL",
			"id_user INTEGER NULL",
			"time TIMESTAMP DEFAULT NOW()"
			"currancy"
			});
	}
};



