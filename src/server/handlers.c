#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foodex_types.h"
#include "handlers.h"
#include "dbconnector.h"

extern MYSQL *con;
extern struct foodex_event_t event;
extern union foodex_data_u data;

struct handler_t* init_handlers()
{
	struct handler_t *chain = malloc(sizeof(struct handler_t));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}
	chain->type = -1;
	chain->next = NULL;
	
	addHandler(chain, AUTHENTICATE_USER, authenticateUser);
	addHandler(chain, ADD_USER_INFO, addUserInfo);
	addHandler(chain, GET_USER_INFO, getUserInfo);
	
	addHandler(chain, ADD_MEAL, addMeal);
	addHandler(chain, GET_MEAL, getMeal);
	addHandler(chain, UPDATE_MEAL, updateMeal);
	addHandler(chain, DELETE_MEAL, deleteMeal);
	
	addHandler(chain, GET_ORDER_LIST, getOrderList);
	addHandler(chain, SELECT_ORDER, selectOrder);
	addHandler(chain, FINISH_ORDER, finishOrder);
	
	addHandler(chain, GET_RESTAURANT_LIST, getRestaurantList);
	addHandler(chain, GET_MENU, getMenu);
	addHandler(chain, ORDER_CART, orderCart);
	
	addHandler(chain, GET_DELIVERY_LIST, getDeliveryList);
	addHandler(chain, CHOOSE_DELIVERY, chooseDelivery);
	addHandler(chain, WITHDRAW_DELIVERY, withdrawDelivery);
	addHandler(chain, FINISH_DELIVERY, finishDelivery);
	
	return chain;
}

void addHandler(struct handler_t *chain, enum foodex_event_type_e type, int (*handler)(struct foodex_event_t *))
{
	struct handler_t *cur_handler = chain;
	while (cur_handler->next)
		cur_handler = cur_handler->next;
		
	struct handler_t *new_handler = (struct handler_t *)malloc(sizeof(struct handler_t));
	new_handler->type = type;
	new_handler->handler = handler;
	new_handler->next = NULL;
	cur_handler->next = new_handler;
}

int handleEvent(struct handler_t *chain, struct foodex_event_t *event)
{	
	struct handler_t *cur_handler = chain;
	while (cur_handler) {
		if (cur_handler->type == event->type)
			return cur_handler->handler(event);

		cur_handler = cur_handler->next;
	}
	
	return 0;
}

int authenticateUser(struct foodex_event_t *event)
{
	printf("[>] Handling event type AUTHENTICATE_USER\n");

	struct foodex_user_t *user = db_get_user_by_phone(con, event->data.user.phone);
	if (user == NULL) return -1;
	
	printf("[<] Successfully handled AUTHENTICATE_USER\n");
	
	data.user = *user;
	free(user);
	if (strcmp(event->data.user.password, data.user.password))
		data.user.id = -1;

	return 0;
}

int addUserInfo(struct foodex_event_t *event)
{
	printf("[>] Handling event type ADD_USER_INFO\n");
	
	db_add_user(con, &event->data.user);
	struct foodex_user_t *user = db_get_user_by_phone(con, event->data.user.phone);
	if (user == NULL) return -1;
		
	printf("[<] Successfully handled ADD_USER_INFO\n");
	
	data.user = *user;
	free(user);
	
	return 1;
}

int getUserInfo(struct foodex_event_t *event)
{
	printf("[>] Handling event type GET_USER_INFO\n");
	
	struct foodex_user_t *user = db_get_user_by_id(con, event->data.user.id);
	if (user == NULL) return -1;
		
	printf("[<] Successfully handled GET_USER_INFO\n");
	
	data.user = *user;
	free(user);
	
	return 0;
}

int getMeal(struct foodex_event_t *event)
{
	printf("[>] Handling event type GET_MEAL\n");
	
	struct foodex_meal_t *meal = db_get_meal_by_id(con, event->data.meal.id);
	if (meal == NULL)
		return 0;
		
	printf("[<] Successfully handled GET_MEAL\n");
	
	data.meal = *meal;
	free(meal);	
	return 0;
}

int addMeal(struct foodex_event_t *event)
{
	printf("[>] Handling event type ADD_MEAL\n");
	
	db_add_meal(con, &event->data.meal, event->data.restaurant.id);
	struct foodex_meal_t *meal = db_get_meal_by_id(con, event->data.restaurant.id);
	if (meal == NULL)
		return -1;
	
	printf("[<] Successfully handled ADD_MEAL\n");
		
	data.meal = *meal;
	free(meal);
	
	return 1;
}

int updateMeal(struct foodex_event_t *event)
{
	printf("[>] Handling event type UPDATE_MEAL\n");
	db_update_meal_by_struct(con, &event->data.meal);
	struct foodex_meal_t *meal = db_get_meal_by_id(con, event->data.meal.id);
	if (meal == NULL)
		return 0;
	
	printf("[<] Successfully handled UPDATE_MEAL\n");
	
	//data.meal = *meal;
	free(meal);
	
	return 1;
}

int deleteMeal(struct foodex_event_t *event)
{
	printf("[>] Handling event type DELETE_MEAL\n");
	
	db_delete_meal_by_id(con, event->data.meal.id);
	struct foodex_meal_t *meal = db_get_meal_by_id(con, event->data.meal.id);
	if (meal != NULL) return 1;
	
	printf("[<] Successfully handled DELETE_MEAL\n");
	
	return 0;
}

int getOrderList(struct foodex_event_t *event)
{
	printf("    Handling event type GET_ORDER_LIST\n");
	
	data.order_list[0] = (struct foodex_order_t){};
}

int selectOrder(struct foodex_event_t *event)
{
	printf("    Handling event type SELECT_ORDER\n");
	
	data.order.restaurant_id = 1;
	//strcpy(data.order.status, str(Preparing));
}

int finishOrder(struct foodex_event_t *event)
{
	printf("    Handling event FINISH_ORDER\n");
	//strcpy(data.order.status, str(Finished));
}

int getRestaurantList(struct foodex_event_t *event) { printf("Handling event type GET_RESTAURANT_LIST\n"); }

int getMenu(struct foodex_event_t *event)
{
	printf("[>] Handling event type GET_MENU\n");
	
	struct foodex_menu_t *menu = db_get_menu(con, event->data.restaurant.id);
	if (menu == NULL) return -1;
		
	printf("[<] Successfully handled GET_MENU\n");	
	
	data.menu = *menu;
	free(menu);
	
	return 0;
}

int orderCart(struct foodex_event_t *event) { printf("    Handling event type ORDER_CART\n"); }
int getDeliveryList(struct foodex_event_t *event) { printf("    Handling event type GET_DELIVERY_LIST\n"); }
int chooseDelivery(struct foodex_event_t *event) { printf("    Handling event type CHOOSE_DELIVERY\n"); }
int withdrawDelivery(struct foodex_event_t *event) { printf("Handling event type WITHDRAW_DELIVERY\n"); }
int finishDelivery(struct foodex_event_t *event) { printf("Handling event type FINISH_DELIVERY\n"); }

