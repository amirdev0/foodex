#include "foodex_types.h"
#include "transmission.h"
#include "customer_api.h"

extern int server_sock;

int rest_get_list(void);

int menu_get_list(int restaurant_id);

int order_create(struct cart_t cart, int customer_id, int restaurant_id);

int order_cancel(int order_id);
