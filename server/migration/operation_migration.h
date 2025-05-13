#include <isce/Schema.h>
#include "Migration.h"



class MigrationOperation : public Migration {
public:
	static void up() {
		Schema::create("operation", {
			"value BIGINT NOT NULL",
			"id_currency INTEGER NOT NULL REFERENCES currency(id)",
			"id_user INTEGER NOT NULL REFERENCES users(id)",
			"time TIMESTAMP DEFAULT NOW()"
			});
	}
};



