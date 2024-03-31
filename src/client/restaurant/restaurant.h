#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "foodex_types.h"

struct menu_t;

int meal_add(struct menu_t *menu, string name, int price, path image);

int meal_modify(struct menu_t *menu, int meal_id, string name, int price, path image);

int meal_remove(struct menu_t *menu, int meal_id);

#endif //RESTAURANT_H
