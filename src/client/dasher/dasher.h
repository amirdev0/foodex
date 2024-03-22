#ifndef DASHER_H
#define DASHER_H

struct foodex_delivery_t {
	int order_id;	
	string delivery_type;
};

int delivery_get_list(void);
int delivery_start(int dasher_id, int order_id);
int delivery_stop(int order_id);
int delivery_finish(int order_id);

#endif //DASHER_H
