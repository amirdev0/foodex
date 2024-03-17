#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodex_types.h"
#include "data_transfer.h"
#include "dasher.h"

extern struct foodex_event_t event;
extern union foodex_data_u data;

int getDeliveryList(void)
{
	event.type = GET_DELIVERY_LIST;

	return transfer(&event, &data);
}

int chooseDelivery(int dasher_id, int order_id)
{
	event.type = CHOOSE_DELIVERY;
	event.data.order.dasher_id = dasher_id;
	event.data.order.id = order_id;

	return transfer(&event, &data);
}

int withdrawDelivery(int dasher_id, int order_id)
{
	event.type = WITHDRAW_DELIVERY;
	event.data.order.dasher_id = dasher_id;
	event.data.order.id = order_id;

	return transfer(&event, &data);
}

int finishDelivery(int dasher_id, int order_id)
{
	event.type = FINISH_DELIVERY;
	event.data.order.dasher_id = dasher_id;
	event.data.order.id = order_id;

	return transfer(&event, &data);
}
