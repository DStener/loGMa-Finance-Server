#include <isce/Schema.h>
#include "Migration.h"



class MigrationOperationAndWall : public Migration {
public:
	static void up() {
		Schema::create("operation_and_wall", {
			"id_operation INTEGER",
			"id_wall INTEGER"
			});
	}
};



