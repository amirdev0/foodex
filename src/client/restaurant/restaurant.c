#include <string.h>

#include "restaurant.h"

struct menu_t {
	struct meal_t {
		int id;
		string name;
		int price;
		path image;
	} meal[MAXSIZE];
};

int meal_add(struct menu_t *menu, string name, int price, path image)
{
	int index = -1;
	for (int i = 0; index < 0 && i < MAXSIZE; i++)
		if (menu->meal[i].id == 0)
			index = i;

	if (index < 0)
		return -1;
	
	menu->meal[index].id = index;
	strncpy(menu->meal[index].name, name, STRSIZE);
	menu->meal[index].price = price;
	strncpy(menu->meal[index].image, image, MAXSIZE);
		
	return 0;
}

int meal_modify(struct menu_t *menu, int meal_id, string name, int price, path image)
{
	int index = -1;
	for (int i = 0; index < 0 && i < MAXSIZE; i++)
		if (menu->meal[i].id == meal_id)
			index = i;
	
	if (index < 0)
		return -1;
	
	menu->meal[index].id = index;
	strncpy(menu->meal[index].name, name, STRSIZE);
	menu->meal[index].price = price;
	strncpy(menu->meal[index].image, image, MAXSIZE);
	
	return 0;	
}

int meal_remove(struct menu_t *menu, int meal_id)
{
	int index = -1;
	for (int i = 0; index < 0 && i < MAXSIZE; i++)
		if (menu->meal[i].id == meal_id)
			index = i;
	
	if (index < 0)
		return -1;
	
	menu->meal[index].id = 0;
	memset(menu->meal[index].name, '\0', STRSIZE);
	menu->meal[index].price = 0;
	memset(menu->meal[index].image, '\0', MAXSIZE);
	
	return 0;	
}
