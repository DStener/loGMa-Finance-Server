#include <isce/Schema.h>
#include "Migration.h"



class MigrationUserAndWall : public Migration {
public:
	static void up() {
		Schema::create("user_and_wall", {
			"id_user INTEGER",
			"id_wall INTEGER",
			"is_admin BOOL"
		});
	}

};



