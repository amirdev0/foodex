#include <sys/socket.h>

#include "foodex_types.h"
#include "data_transfer.h"

extern int server_sock;

int transfer(struct foodex_event_t *event, union foodex_data_u *data)
{
	if (send(server_sock, event, sizeof(struct foodex_event_t), 0) == 0)
		return 0;

	if (recv(server_sock, data, sizeof(union foodex_data_u), MSG_WAITALL) == 0)
		return 0;
	
	return 1;
}
