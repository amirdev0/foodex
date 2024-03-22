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

int getRestaurantList(void);
int getMenuList(int restaurant_id);

int createOrder(struct cart_t cart, int customer_id, int restaurant_id);
int cancelOrder(int order_id);

int addItem(struct cart_t *cart, int meal_id, int quantity);
int removeItem(struct cart_t *cart, int meal_id, int quantity);

#endif //CUSTOMER_H
