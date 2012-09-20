#ifndef SERVER_H_
#define SERVER_H_


// these in the future will be located in /etc/mediad/ or something like that
#define MODULES_PATH 		"./modules/"
#define CONFIG_PATH			"./server.conf"

/*
	Only using this macro if the config file doesn`t contain a port number, 
	so we don`t have to suspend the system init process
*/
#define DEFAULT_SERVER_PORT	8080

#endif /* SERVER_H_ */


