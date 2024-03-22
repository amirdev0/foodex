#include <sys/socket.h>

#include "foodex_types.h"
#include "transmission.h"

struct foodex_event_t transmit(struct foodex_event_t request, int server_sock)
{
	struct foodex_event_t response;
	
	if (send(server_sock, &request, sizeof(struct foodex_event_t), 0) == 0)
		return (struct foodex_event_t){ .result = FAIL };
	
	if (recv(server_sock, &response, sizeof(struct foodex_event_t), MSG_WAITALL) == 0)
		return (struct foodex_event_t){ .result = FAIL };
	
	return response;
}
