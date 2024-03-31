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
	add_handler(&chain, SET_USER_INFO, set_user_info);
	
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

int set_user_info(struct foodex_event_t *event)
{
	struct user_t user;
	strncpy(user.name, event->data.atomic.user_name, STRSIZE);
	strncpy(user.email, event->data.atomic.user_email, STRSIZE);
	strncpy(user.address, event->data.atomic.user_address, STRSIZE);
	strncpy(user.image, event->data.atomic.user_image, MAXSIZE);
	db_create_user(user);
	
	event->result = SUCCESS;
	
	return 0;
}
