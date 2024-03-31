#include <string.h>

#include "foodex_types.h"
#include "transmission.h"
#include "dasher_api.h"

extern int server_sock;

struct deliv_list_t {
	struct deliv_t {
		int order_id;
		string customer_address;
		string restaurant_address;
	} deliv[MAXSIZE];
};

struct deliv_list_t delivery_get_list(void)
{
	struct foodex_event_t event = { .type = GET_ORDER_LIST };
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct deliv_list_t){ 0 };
	
	struct deliv_list_t deliv_list;
	for (int i = 0; i < MAXSIZE; i++) {
		deliv_list.deliv[i].order_id = event.data.array.delivery[i].order_id;
		strncpy(deliv_list.deliv[i].customer_address, event.data.array.delivery[i].customer_address, STRSIZE);
		strncpy(deliv_list.deliv[i].restaurant_address, event.data.array.delivery[i].restaurant_address, STRSIZE);
	}
	
	return deliv_list;
}

int delivery_start(int order_id, int dasher_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	event.data.atomic.order_id = order_id;
	event.data.atomic.dasher_id = dasher_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return 0;
}

int delivery_stop(int order_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	event.data.atomic.order_id = order_id;
	event.data.atomic.dasher_id = -1;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return 0;
}
