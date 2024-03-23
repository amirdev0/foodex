#include "restaurant.h"

int meal_create(struct menu_t *menu, string name, int price, path image);

int meal_update(struct menu_t *menu, int meal_id, int price, path image);

int meal_delete(struct menu_t *menu, int meal_id);
