#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "foodex_types.h"
#include "connection.h"
#include "user_api.h"
#include "restaurant_api.h"
#include "restaurant.h"

int server_sock;

void app_run(void)
{
	int id;
	string phone;
	string password;
	
	while (true) {
		printf("Enter phone: ");
		scanf("%255s", phone);
		printf("Enter password: ");
		scanf("%255s", password);
	
		id = user_auth(phone, password);
		if (id > -1)
			break;
		
		puts("Authentication failed!");
	}
	puts("Authentication succeed!");
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
