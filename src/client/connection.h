#ifndef CONNECTION_H
#define CONNECTION_H

int con_open(int port, char *ip);
void con_close(int server_sock);

#endif //CONNECTION_H
