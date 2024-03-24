#ifndef CUSTOMER_API_H
#define CUSTOMER_API_H

struct cart_t;

int rest_get_list(void);
int menu_get_list(int restaurant_id);

int order_create(struct cart_t cart, int customer_id, int restaurant_id);
int order_cancel(int order_id);

#endif //CUSTOMER_API_H
