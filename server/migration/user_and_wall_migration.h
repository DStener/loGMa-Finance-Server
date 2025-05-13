#include <isce/Schema.h>
#include "Migration.h"



class MigrationUserAndWall : public Migration {
public:
	static void up() {
		Schema::create("user_and_wall", {
			"id_user INTEGER NOT NULL REFERENCES users(id)",
			"id_wall INTEGER NOT NULL REFERENCES wall(id)",
			"is_admin BOOL DEFAULT false"
		});
	}

};



