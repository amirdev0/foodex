#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "foodex_types.h"

struct foodex_event_t transmit(struct foodex_event_t request, int server_sock);

#endif //TRANSMISSION_H
