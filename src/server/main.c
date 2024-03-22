#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()
#include <signal.h>     //SIGINT, signal()
#include <pthread.h>    //pthread_t, pthread_create(), pthread_join()
#include <semaphore.h>  //sem_t, sem_init(), sem_wait(), sem_post(), sem_destroy()
#include <errno.h>      //perror()
#include <stdbool.h>
#include <mysql.h>		//MYSQL

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodex_types.h"
#include "dbconnector.h"
#include "handlers.h"

#define MAXCLIENTS 10

struct thread_args {
	int client_count;
	int client_sock;
	struct handler_t *chain;
};

struct foodex_event_t event;

MYSQL *con;
int server_sock;
sem_t mutex;

void sig_handler(int signum)
{
	if (close(server_sock) < 0)	{
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("\b\b[-] Server was stopped\n");
	exit(0);
}

void* client_handler(void *vargp)
{
	struct thread_args *thread_args = vargp;
	int bytes_read, client_sock, client_count;
	struct handler_t *chain;
	
	client_count = thread_args->client_count;
	client_sock = thread_args->client_sock;
	chain = thread_args->chain;
	
	printf("[+] Thread for client #%d was created\n", client_count);

	while (true) {
	  	//sem_wait(&mutex);
		bytes_read = recv(client_sock, &event, sizeof(event), MSG_WAITALL);
		
		if (bytes_read <= 0) {
			printf("[-] Client #%d stopped\n", client_count);
			//sem_post(&mutex);
			return NULL;
		}

		printf("[?] From Client #%d was reveived event (%d KB)\n", client_count, bytes_read / 1024);
		
		if (!handle_event(chain, &event))
			printf("[x] Failed to handle event\n");
		
		send(client_sock, &event, sizeof(event), 0);
		//sem_post(&mutex);
	}
	
	return NULL;
}

int main(int argc, char * argv[])
{
	sem_init(&mutex, 0, 1);
	signal(SIGINT, sig_handler);
	con = db_init();

	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";

	int client_sock[MAXCLIENTS];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	pthread_t tid[MAXCLIENTS];
	struct handler_t *chain;
	
	chain = chain_init();
	if (chain == NULL) {
		fprintf(stderr, "[!] Failed to initialize handlers.\n");
		exit(1);
	}
 	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created\n");
 
	memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	if (inet_aton(ip, &server_addr.sin_addr) == 0) {
		fprintf(stderr, "[!] Invalid IPv4 address\n");
		exit(1);
	}
	printf("[+] Asigned IPv4 address: %s\n", ip);
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 0, 0);
 
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("[!] Server can't bind to port");
		exit(1);
	}
	printf("[+] Bound to the port number: %d\n", port);
 
	if (listen(server_sock, 1) < 0)	{
		perror("[!] Listen failed");
		exit(1);
	}
	printf("[+] Listening...\n");

	for (int i = 0; i < MAXCLIENTS; ++i) {
		addr_size = sizeof(client_addr);
		client_sock[i] = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
		if (client_sock[i] < 0) {
			perror("[!] Socket for client was not created");
			exit(1);
		}
		printf("[+] Client #%d connected\n", i + 1);

		struct thread_args thread_args = { i + 1, client_sock[i], chain };
		pthread_create(&tid[i], NULL, client_handler, &thread_args);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		pthread_join(tid[i], NULL);
		printf("[-] Thread for client #%d terminated\n", i + 1);
	}
	
	for (int i = 0; i < MAXCLIENTS; ++i) {
		if (close(client_sock[i]) < 0) {
			perror("[!] Client socket was not closed");
			exit(1);
		}
		printf("[-] Client #%d disconnected\n", i + 1);
	}
	
	if (close(server_sock) < 0) {
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("[-] Server was stopped\n");
	
	mysql_close(con);
	sem_destroy(&mutex);

	return 0;
}
