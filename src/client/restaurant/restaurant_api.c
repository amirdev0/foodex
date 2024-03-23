#include "foodex_types.h"
#include "transmission.h"
#include "restaurant_api.h"

extern int server_sock;

struct menu_t menu_get_list(int restaurant_id);

int menu_set_list(struct menu_t menu);

struct draft_t draft_get_list(int restaurant_id);

int draft_accept(struct draft_t *draft, int restaurant_id);

int draft_revoke(int order_id);

int draft_finish(int order_id);
