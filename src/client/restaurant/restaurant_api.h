#ifndef RESTAURANT_API_H
#define RESTAURANT_API_H

#include "foodex_types.h"

struct draft_t {
	int order_id;
	struct item_t {
		int id;
		string name;
		int quantity;
	} item[MAXSIZE];
};

//struct menu_t menu_get_list(int restaurant_id);
//int menu_set_list(struct menu_t menu);

struct draft_t draft_get_list(int restaurant_id);
int draft_accept(struct draft_t *draft, int restaurant_id);
int draft_revoke(int order_id);
int draft_finish(int order_id);

#endif //RESTAURANT_API_H
