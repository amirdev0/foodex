#ifndef DASHER_API_H
#define DASHER_API_H

struct deliv_list_t delivery_get_list(void);

int delivery_start(int dasher_id, int order_id);

int delivery_stop(int order_id);

#endif //DASHER_API_H
