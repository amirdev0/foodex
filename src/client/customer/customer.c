#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "foodex_types.h"
#include "data_transfer.h"
#include "customer.h"

extern struct foodex_event_t event;
extern union foodex_data_u data;

struct foodex_cart_t {
	struct foodex_item_t {
		struct foodex_meal_t meal;
		int quantity;
		float net_price;
	};
	int total_price;
};

void viewCart(void)
{
	//printing the cart
	printf("Cart:\n");
	for(int i = 0; i < data.order.cart.item[i].quantity; i++)
		printf("%d. %s\n", i+1, data.order.cart.item[i].meal.name);
}

int getRestaurantList(void)
{
	event.type = GET_RESTAURANT_LIST;

	return transfer(&event, &data);
}

int getMenu(int restaurantID)
{
	event.type = GET_MENU;
	event.data.restaurant.id = restaurantID;

	return transfer(&event, &data);
}

int orderCart(struct foodex_order_t order)
{
	event.type = ORDER_CART;
	event.data.order = order;

	return transfer(&event, &data);
}

