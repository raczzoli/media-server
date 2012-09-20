#include "server/server.h"
#include "server/core.h"
#include "server/module.h"
#include "server/config.h"
#include "server/connection.h"


void free_server();

int main()
{
	int server_port			= 0;
	char *tmp_port_val		= NULL;
	int server_descriptor	= 0;
	
	if (config_load(CONFIG_PATH) != 0)
	{
		return EXIT_FAILURE;
	}
	
	if (module_load(MODULES_PATH) != 0)
	{
		free_server();
		return EXIT_FAILURE;
	}
	
	tmp_port_val = (char*)config_get_entry_value("port");
	if (tmp_port_val == NULL)
	{
		server_port = DEFAULT_SERVER_PORT;
		log_message("%s%d%s\n", "No port number was specified in server.conf! Using default (", server_port, ").");
	}
	else if ((server_port = atoi(tmp_port_val)) < 1)
	{
		server_port = DEFAULT_SERVER_PORT;
		log_message("%s%d%s\n", "Invalid port number was specified in server.conf! Using default (", server_port, ").");
	}
	
	if ((server_descriptor = connection_init(server_port)) > 0)
	{
		
	}
	
	free_server();
	return 0;
}


void free_server()
{
	/* freeing loaded config entries */
	config_free_entries();

	/* unloading server modules */
	module_unload();
}