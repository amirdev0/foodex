#include <stdlib.h>

#include "foodex_types.h"
#include "connection.h"
#include "user_api.h"
#include "dasher_api.h"
#include "dasher.h"

int server_sock;

void app_run(void)
{

}

int main(int argc, char *argv[])
{
	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";
	
	server_sock = con_open(port, ip);
	
	app_run();
	
	con_close(server_sock);
	
	return 0;
}
