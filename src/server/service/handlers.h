#ifndef HANDLERS_H
#define HANDLERS_H

struct handler_t {
	enum foodex_event_type_e type;
	int (*handler)(struct foodex_event_t *);
	struct handler_t *next;
};

struct handler_t* chain_init(void);

void handler_add(struct handler_t *chain, enum foodex_event_type_e, int (*handler)(struct foodex_event_t *));

int event_handle(struct handler_t *, struct foodex_event_t *);

//handlers are mainly intended for calling certain function(s) from dbconnector

#endif //HANDLERS_H
