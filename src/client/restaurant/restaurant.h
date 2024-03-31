#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "foodex_types.h"

struct menu_t {
	struct meal_t {
		int id;
		string name;
		int price;
		path image;
	} meal[MAXSIZE];
};

int meal_create(struct menu_t *menu, string name, int price, path image);
int meal_update(struct menu_t *menu, int meal_id, int price, path image);
int meal_delete(struct menu_t *menu, int meal_id);

#endif //RESTAURANT_H
