#ifndef DASHER_H
#define DASHER_H

struct foodex_delivery_t {
	int order_id;	
	string delivery_type;
};

int getDeliveryList(void);
int takeDelivery(int dasher_id, int order_id);
int withdrawDelivery(int order_id);
int giveDelivery(int order_id);

#endif //DASHER_H
