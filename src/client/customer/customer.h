#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "foodex_types.h"

struct cart_t {
	struct foodex_item_t {
		int meal_id;
		string name;
		int quantity;
		int net_price;
	} item[MAXSIZE];
	double total_price;
};

int item_add(struct cart_t *cart, int meal_id, int quantity);
int item_remove(struct cart_t *cart, int meal_id, int quantity);

#endif //CUSTOMER_H
