#include <isce/Schema.h>
#include "Migration.h"



class MigrationOperationAndWall : public Migration {
public:
	static void up() {
		Schema::create("operation_and_wall", {
			"id_operation INTEGER NOT NULL REFERENCES operation(id)",
			"id_wall INTEGER NOT NULL REFERENCES wall(id)",
			"UNIQUE (id_operation, id_wall)",
			});
	}
};



