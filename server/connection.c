#include "connection.h"



int connection_init(int port)
{
	int optval 		= 1;
	int descriptor 	= 0;
	struct sockaddr_in addr;

	descriptor = socket(AF_INET, SOCK_STREAM, 0);
	
	if (descriptor < 0)
	{
		log_error("%s\n","Unable to create socket for connection!");
		return -1;
	}
	
	addr.sin_family 		= AF_INET;
	addr.sin_addr.s_addr 	= INADDR_ANY;
	addr.sin_port 			= htons(port);
	
	setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

	if (bind(descriptor, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		log_error("%s%d!\n","Unable to bind the socket to port: ", port);
		return -1;
	}

	return descriptor;
}


int connection_start_listening(int descriptor, int max_pending_clients)
{
	return 0;
}

