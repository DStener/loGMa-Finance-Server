#include <isce/Schema.h>
#include "Migration.h"



class MigrationOperation : public Migration {
public:
	static void up() {
		Schema::create("operation", {
			"value BIGINT",
			"id_currency INTEGER",
			"id_user INTEGER",
			"time TIMESTAMP DEFAULT NOW()"
			});
	}
};



