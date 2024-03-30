#ifndef CUSTOMER_API_H
#define CUSTOMER_API_H

struct cart_t;

struct rest_list_t;

struct menu_list_t;

struct rest_list_t rest_get_list(void);

struct menu_list_t menu_get_list(int rest_id);

int order_create(struct cart_t cart, int cust_id, int rest_id);

int order_cancel(int order_id);

#endif //CUSTOMER_API_H
