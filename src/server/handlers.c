#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foodex_types.h"
#include "handlers.h"
#include "dbconnector.h"

extern MYSQL *con;
extern struct foodex_event_t event;

struct handler_t* chain_init()
{
	struct handler_t *chain = malloc(sizeof(struct handler_t));
	if (chain == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}
	chain->type = -1;
	chain->next = NULL;
	
	//add_handler(chain, AUTHENTICATION, authenticate);
	
	return chain;
}

void add_handler(struct handler_t *chain, enum foodex_event_type_e type, int (*handler)(struct foodex_event_t *))
{
	struct handler_t *cur_handler = chain;
	while (cur_handler->next)
		cur_handler = cur_handler->next;
		
	struct handler_t *new_handler = (struct handler_t *)malloc(sizeof(struct handler_t));
	new_handler->type = type;
	new_handler->handler = handler;
	new_handler->next = NULL;
	cur_handler->next = new_handler;
}

int handle_event(struct handler_t *chain, struct foodex_event_t *event)
{	
	struct handler_t *cur_handler = chain;
	while (cur_handler) {
		if (cur_handler->type == event->type)
			return cur_handler->handler(event);

		cur_handler = cur_handler->next;
	}
	
	return 0;
}
