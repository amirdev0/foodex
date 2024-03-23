#include "foodex_types.h"
#include "transmission.h"
#include "dasher_api.h"

int delivery_get_list(void);

int delivery_start(int dasher_id, int order_id);

int delivery_stop(int order_id);

int delivery_finish(int order_id);
