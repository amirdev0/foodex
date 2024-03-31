#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foodex_types.h"
#include "dbtypes.h"
#include "dbconnector.h"
#include "handlers.h"

extern MYSQL *con;
extern struct foodex_event_t event;

struct handler_t* chain_init()
{
	static struct handler_t chain = { -1, NULL, NULL };
	
	add_handler(&chain, AUTHENTICATION, authenticate);
	
	return &chain;
}

void chain_free(struct handler_t *chain)
{
	if (chain->next)
		chain_free(chain->next);
	
	if (chain->type != (enum foodex_event_type_e)-1)
		free(chain);
}

void add_handler(struct handler_t *chain, enum foodex_event_type_e type, int (*handler)(struct foodex_event_t *))
{
	struct handler_t *cur_handler = chain;
	while (cur_handler->next)
		cur_handler = cur_handler->next;
		
	struct handler_t *new_handler = malloc(sizeof(struct handler_t));
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

int authenticate(struct foodex_event_t *event)
{	
	printf("[?] Handling authentiation of phone: %s\n", event->data.atomic.phone);
	
	string password;
	db_read_password(con, password, event->data.atomic.phone);
	
	if (strcmp(password, event->data.atomic.password)) {
		event->result = FAIL;
		return -1;
	}
	
	strncpy(event->data.atomic.password, password, STRSIZE);
	event->result = SUCCESS;
	
	return 0;
}
