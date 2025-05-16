#include <isce/Schema.h>
#include "Migration.h"



class MigrationCurrency : public Migration {
public:
	static void up() {
		Schema::create("currency", {
			"name VARCHAR(255) NOT NULL",
			"sign CHAR NOT NULL UNIQUE",
			});
	}
};



