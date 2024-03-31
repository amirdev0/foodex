#include <string.h>

#include "foodex_types.h"
#include "transmission.h"
#include "customer_api.h"

struct menu_list_t {
	struct meal_t {
		int id;
		string name;
		int cost;
		path image;
	} meal[MAXSIZE];
};

struct rest_list_t {
	struct rest_t {
		int id;
		string name;
		string address;
		path image;
	} rest[MAXSIZE];
};

struct cart_t {
	int item_count;
	struct item_t {
		int meal_id;
		string name;
		int quantity;
		int cost;
		int net_price;
	} item[MAXSIZE];
	double total_price;
};

extern int server_sock;

struct rest_list_t rest_get_list(void)
{
	struct foodex_event_t event = { .type = GET_REST_LIST };
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct rest_list_t){ 0 };
	
	struct rest_list_t rest_list;
	for (int i = 0; i < MAXSIZE; i++) {
		rest_list.rest[i].id = event.data.array.restaurant[i].id;
		strncpy(rest_list.rest[i].name, event.data.array.restaurant[i].name, STRSIZE);
		strncpy(rest_list.rest[i].address, event.data.array.restaurant[i].address, STRSIZE);
		strncpy(rest_list.rest[i].image, event.data.array.restaurant[i].image, MAXSIZE);
	}
	
	return rest_list;
}

struct menu_list_t menu_get_list(int rest_id)
{
	struct foodex_event_t event = { .type = GET_REST_INFO };
	event.data.atomic.restaurant_id = rest_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct menu_list_t){ 0 };
	
	struct menu_list_t menu_list;
	for (int i = 0; i < MAXSIZE; i++) {
		menu_list.meal[i].id = event.data.array.menu.meal[i].id;
		strncpy(menu_list.meal[i].name, event.data.array.menu.meal[i].name, STRSIZE);
		menu_list.meal[i].cost = event.data.array.menu.meal[i].price;
		strncpy(menu_list.meal[i].image, event.data.array.menu.meal[i].image, MAXSIZE);
	}
	
	return menu_list;
}

int order_create(struct cart_t cart, int cust_id, int rest_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	for (int i = 0; i < MAXSIZE; i++) {
		event.data.array.order.unit[i].meal_id = cart.item[i].meal_id;
		event.data.array.order.unit[i].quantity = cart.item[i].quantity;
	}
	event.data.atomic.customer_id = cust_id;
	event.data.atomic.restaurant_id = rest_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return event.data.atomic.order_id;
}

int order_cancel(int order_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	for (int i = 0; i < MAXSIZE; i++) {
		event.data.array.order.unit[i].meal_id = 0;
		event.data.array.order.unit[i].quantity = 0;
	}
	event.data.atomic.order_id = order_id;
	event.data.atomic.customer_id = 0;
	event.data.atomic.restaurant_id = 0;
	event = transmit(event, server_sock);

	if (event.result == FAIL)
		return -1;
	
	return 0;
}
