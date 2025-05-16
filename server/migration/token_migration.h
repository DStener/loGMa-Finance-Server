#include <isce/Schema.h>
#include "Migration.h"



class MigrationToken : public Migration {
public:
	static void up()  {
		Schema::create("token", { 
					"token VARCHAR", 
					"id_user INTEGER", 
					"time TIMESTAMP" });
	}
};



