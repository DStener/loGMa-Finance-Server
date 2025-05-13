#include <isce/Schema.h>
#include "Migration.h"



class MigrationRuleAutoAdd : public Migration {
public:
	static void up() {
		Schema::create("rule_auto_add", {
			"id_category INTEGER NOT NULL",
			"id_wall INTEGER NOT NULL REFERENCES wall(id)",
			});
	}
};



