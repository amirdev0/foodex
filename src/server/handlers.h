#include "foodex_types.h"

struct handler_t {
	enum foodex_event_type_e type;
	int (*handler)(struct foodex_event_t *);
	struct handler_t *next;
};

struct handler_t* init_handlers(void);
void addHandler(struct handler_t *, enum foodex_event_type_e, int (*)(struct foodex_event_t *));

int handleEvent(struct handler_t *, struct foodex_event_t *);

//handlers are mainly intended for calling certain function(s) from dbconnector
//and parse retreived table or json file to union data
int authenticateUser(struct foodex_event_t *);
int addUserInfo(struct foodex_event_t *);
int getUserInfo(struct foodex_event_t *);

int addMeal(struct foodex_event_t *);
int getMeal(struct foodex_event_t *);
int updateMeal(struct foodex_event_t *);
int deleteMeal(struct foodex_event_t *);

int getOrderList(struct foodex_event_t *);
int selectOrder(struct foodex_event_t *);
int finishOrder(struct foodex_event_t *);

int getRestaurantList(struct foodex_event_t *);
int getMenu(struct foodex_event_t *);
int orderCart(struct foodex_event_t *);

int getDeliveryList(struct foodex_event_t *);
int chooseDelivery(struct foodex_event_t *);
int withdrawDelivery(struct foodex_event_t *);
int finishDelivery(struct foodex_event_t *);

