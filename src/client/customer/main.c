#include <stdlib.h>

#include "foodex_types.h"
#include "connection.h"
#include "account.h"
#include "customer.h"

int server_sock;

void run_app(void)
{

}

int main(int argc, char *argv[])
{
	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";
	
	server_sock = open_con(port, ip);
	
	run_app();
	
	close_con(server_sock);
	
	return 0;
}
