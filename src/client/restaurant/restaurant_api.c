#include <string.h>

#include "foodex_types.h"
#include "transmission.h"
#include "restaurant_api.h"

extern int server_sock;

struct menu_t {
	struct meal_t {
		int id;
		string name;
		int price;
		path image;
	} meal[MAXSIZE];
};

struct draft_t {
	int order_id;
	struct item_t {
		int meal_id;
		string name;
		int quantity;
	} item[MAXSIZE];
};

struct menu_t menu_get_list(int restaurant_id)
{
	struct foodex_event_t event = { .type = GET_REST_INFO };
	event.data.atomic.restaurant_id = restaurant_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct menu_t){ 0 };
	
	struct menu_t menu;
	for (int i = 0; i < MAXSIZE; i++) {
		menu.meal[i].id = event.data.array.menu.meal[i].id;
		strncpy(menu.meal[i].name, event.data.array.menu.meal[i].name, STRSIZE);
		menu.meal[i].price = event.data.array.menu.meal[i].price;
		strncpy(menu.meal[i].image, event.data.array.menu.meal[i].image, MAXSIZE);
	}
	
	return menu;
}

int menu_set_list(int restaurant_id, struct menu_t menu)
{
	struct foodex_event_t event = { .type = SET_REST_INFO };
	event.data.atomic.restaurant_id = restaurant_id;
	for (int i = 0; i < MAXSIZE; i++) {
		event.data.array.menu.meal[i].id = menu.meal[i].id;
		strncpy(event.data.array.menu.meal[i].name, menu.meal[i].name, STRSIZE);
		event.data.array.menu.meal[i].price = menu.meal[i].price;
		strncpy(event.data.array.menu.meal[i].image, menu.meal[i].image, MAXSIZE);
	}
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
		
	return 0;
}

struct draft_t draft_get_list(int restaurant_id)
{
	struct foodex_event_t event = { .type = GET_ORDER_LIST };
	event.data.atomic.restaurant_id = restaurant_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct draft_t){ 0 };
	
	struct draft_t draft;
	draft.order_id = event.data.atomic.order_id;
	for (int i = 0; i < MAXSIZE; i++) {
		draft.item[i].meal_id = event.data.array.draft.item[i].meal_id;
		strncpy(draft.item[i].name, event.data.array.draft.item[i].name, STRSIZE);
		draft.item[i].quantity = event.data.array.draft.item[i].quantity;
	}
	
	return draft;
}

int draft_accept(int order_id, int restaurant_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	event.data.atomic.order_id = order_id;
	event.data.atomic.restaurant_id = restaurant_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return 0;
}

int draft_revoke(int order_id)
{
	struct foodex_event_t event = { .type = SET_ORDER_INFO };
	event.data.atomic.order_id = order_id;
	event.data.atomic.restaurant_id = 0;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return 0;
}
