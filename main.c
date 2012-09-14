#include "server/server.h"
#include "server/core.h"
#include "server/module.h"
#include "server/config.h"


int main()
{
	/* module.c tests */
	module_load(MODULES_PATH);
	module_unload();
	
	/* config.c tests */
	config_load(CONFIG_PATH);
	
	printf("port value: %s\n", (char *)config_get_entry_value("port"));
	printf("url value: %s\n", (char *)config_get_entry_value("url"));
	
	config_free_entries();
	
	return 0;
}
