#pragma once

#include <isce/Schema.h>
#include "Migration.h"

class MigrationCurrencyAndWall : public Migration {
public:
	static void up() {
		Schema::create("currency_and_wall", {
			"id_wall INTEGER NOT NULL REFERENCES wall(id)",
			"iso_currency VARCHAR(3) NOT NULL REFERENCES currency(id)",
			"UNIQUE(id_wall,id_currency)"
		});
	}
};



