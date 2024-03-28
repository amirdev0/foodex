#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "connection.h"

int con_open(int port, char *ip)
{
	int server_sock;
	struct sockaddr_in addr;
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created\n");
	
	memset(&addr, '\0', sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	
	if (connect(server_sock, (struct sockaddr *)&addr, sizeof (addr)) < 0)	{
		perror("[!] Failed to connect to the server");
		exit(1);
	}
	printf("[+] Connected to the server\n");
	
	return server_sock;
}

void con_close(int server_sock)
{
	if (close(server_sock) < 0) {
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("[-] Disconnected from the server\n");
}
