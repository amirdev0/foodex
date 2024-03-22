#ifndef RESTAURANT_H
#define RESTAURANT_H

#define MAXSIZE 256

struct menu_t {
	struct meal_t {
		int id;
		string name;
		int price;
		path image
	} meal[MAXSIZE];
};

struct draft_t {
	int order_id;
	struct item_t {
		int id;
		string name;
		int quantity;
	} item[MAXSIZE];
};

struct menu_t menu_get_list(int restaurant_id);
int menu_set_list(struct menu_t menu);

int meal_create(struct menu_t *menu, string name, int price, path image);
int meal_update(struct menu_t *menu, int meal_id, int price, path image);
int meal_delete(struct menu_t *menu, int meal_id);

struct draft_t draft_get_list(int restaurant_id);
int draft_accept(struct draft_t *draft, int restaurant_id);
int draft_revoke(int order_id);
int draft_finish(int order_id);

#endif //RESTAURANT_H
