#include <isce/Schema.h>
#include "Migration.h"



class MigrationCategory : public Migration {
public:
	static void up() {
		Schema::create("category", {
			"icon INTEGER",
			"name VARCHAR(255)",
			"id_wall INTEGER",
			});
	}
};



