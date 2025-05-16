#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationOperationAndCategory : public Migration {
public:
	static void up() {
		Schema::create("operation_and_category", {
			"id_operation INTEGER NOT NULL REFERENCES operation(id)",
			"id_category INTEGER NOT NULL REFERENCES category(id)",
			"UNIQUE(id_operation, id_category)",
			});
	}
};



