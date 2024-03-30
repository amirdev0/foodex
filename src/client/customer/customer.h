#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "foodex_types.h"

struct cart_t;

int item_add(struct cart_t *cart, int meal_id, int quantity, int cost, string name);

int item_remove(struct cart_t *cart, int meal_id, int quantity);

#endif //CUSTOMER_H
