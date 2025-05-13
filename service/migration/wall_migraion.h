#include <isce/Schema.h>
#include "Migration.h"



class MigrationWall : public Migration {
public:
	static void up() {
		Schema::create("wall", {
			"name VARCHAR(255)",
			"is_group INTEGER",
			"is_public INTEGER",
			});
	}

};



