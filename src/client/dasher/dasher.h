#ifndef DASHER_H
#define DASHER_H

int getDeliveryList(void);
int chooseDelivery(int dasher_id, int order_id);
//Selects a specific order delivery from a list of available order deliveries to perform actions on. Returns 1 on success, 0 otherwise.

int withdrawDelivery(int dasher_id, int order_id);
//Withdraws an order delivery. Returns 1 on success, 0 otherwise.

int finishDelivery(int dasher_id, int order_id);
//Marks an order delivery as finished. Returns 1 on success, 0 otherwise.

#endif
