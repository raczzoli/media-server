#include "server/server.h"
#include "server/core.h"
#include "server/module.h"
#include "server/config.h"

int main()
{
	/* module.c tests */
	module_load(MODULES_PATH);
	module_unload();
	
	/* module.h tests */
	config_load(CONFIG_PATH);
	config_free_entries();
	
	return 0;
}
