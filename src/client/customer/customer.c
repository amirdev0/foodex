#include "customer.h"

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

int item_add(struct cart_t *cart, int meal_id, int quantity, int cost, string name)
{
	int index = -1;
	for (int i = 0; index < 0 && i < MAXSIZE; i++)
		if (cart->item[i].meal_id == meal_id)
			index = i;
	
	if (index < 0) {
		cart->item[cart->item_count].meal_id = meal_id;
		cart->item[cart->item_count].quantity = quantity;
		cart->item[cart->item_count].cost = cost;
		cart->item[cart->item_count].net_price = cost * quantity;
		strncpy(cart->item[cart->item_count - 1].name, name, STRSIZE);
		cart->item_count++;
	} else {
		cart->item[index].quantity += quantity;
		cart->item[index].net_price = cost * quantity;
	}
	
	cart->total_price = 0;
	for (int i = 0; i < MAXSIZE; i++)
		cart->total_price += cart->item[i].net_price;
	
	return 0;
}

int item_remove(struct cart_t *cart, int meal_id, int quantity)
{
	for (int i = 0; i < MAXSIZE; i++) {
		if (cart->item[i].meal_id == meal_id) {
			if (cart->item[i].quantity > quantity) {
				cart->item[i].quantity -= quantity;
			} else {
				cart->item[i].meal_id = 0;
				cart->item[i].cost = 0;
				cart->item[i].quantity = 0;
				memset(cart->item[i].name, '\0', STRSIZE);
			}
			cart->item[i].net_price = cart->item[i].cost * cart->item[i].quantity;
			break;
		}
	}
	
	cart->total_price = 0;
	for (int i = 0; i < MAXSIZE; i++)
		cart->total_price += cart->item[i].net_price;
		
	return 0;
}
