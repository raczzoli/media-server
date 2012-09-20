#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"
#include "core.h"

/*
	Creates a socket and binds it to the specified port.
	Returns -1 if init failed, and a socket descriptor if succeded
*/
int connection_init(int port);

int connection_start_listening(int descriptor, int max_pending_clients);

#endif /* CONNECTION_H_ */
