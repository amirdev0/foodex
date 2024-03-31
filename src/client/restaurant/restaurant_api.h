#ifndef RESTAURANT_API_H
#define RESTAURANT_API_H

struct menu_t;

struct draft_t;

struct menu_t menu_get_list(int restaurant_id);

int menu_set_list(int restaurant_id, struct menu_t menu);

struct draft_t draft_get_list(int restaurant_id);

int draft_accept(int order_id, int restaurant_id);

int draft_revoke(int order_id);

#endif //RESTAURANT_API_H
