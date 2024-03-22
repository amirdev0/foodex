#ifndef CUSTOMER_H
#define CUSTOMER_H

struct cart_t {
	struct foodex_item_t {
		int meal_id;
		string name;
		int quantity;
		int net_price;
	} item[MAXSIZE];
	double total_price;
};

int rest_get_list(void);
int menu_get_list(int restaurant_id);

int order_create(struct cart_t cart, int customer_id, int restaurant_id);
int order_cancel(int order_id);

int item_add(struct cart_t *cart, int meal_id, int quantity);
int item_remove(struct cart_t *cart, int meal_id, int quantity);

#endif //CUSTOMER_H
