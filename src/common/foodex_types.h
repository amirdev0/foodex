#ifndef FOODEX_TYPES_H
#define FOODEX_TYPES_H

#define str(x) #x
#define STRSIZE 63
#define PATHSIZE 255
#define MAXSIZE 255

struct foodex_user_t;
struct foodex_dasher_t;
struct foodex_restaurant_t;
struct foodex_order_t;
struct foodex_event_t;

typedef char string[STRSIZE];
typedef char path[PATHSIZE];

struct foodex_user_t {
	int id;
	string phone;
	string password;
	enum foodex_user_type_e {
		Customer,
		Dasher,
		Restaurant
	} type;
	string name;
	string email;
	string address;
	path image;
};

struct foodex_dasher_t {
	struct foodex_user_t user;
	struct foodex_delivery_t {		
		string delivery_type;
	} delivery;
};

struct foodex_restaurant_t {
	struct foodex_user_t user;
	struct foodex_menu_t {
		struct foodex_meal_t {
			int id;
			string name;
			float price;
			path image
		} meal[MAXSIZE];
	} menu;
};

struct foodex_order_t {
	int id;
	int customer_id;
	string opened_time;
	string closed_time;
	enum foodex_order_status_e {
		Placed,
		Preparing,
		Delivering,
		Finished
	} status;
	struct foodex_food_t {
		int restaurant_id;
		struct foodex_item_t {
			int meal_id;
			int quantity;
		} item[MAXSIZE];
	} food;
	struct foodex_shipping_t {
		int dasher_id;
		string restaurant_addr;
		string customer_addr;
		string shipping_type;
	} shipping;
};

struct foodex_event_t {
	enum foodex_event_type_e {
		AUTHENTICATION,
		GET_USER_INFO,
		SET_USER_INFO,
		GET_DASH_INFO,
		SET_DASH_INFO,
		GET_REST_INFO,
		SET_REST_INFO,	
		GET_ORDER_INFO,
		SET_ORDER_INFO,
	} type;
	
	union foodex_data_u {
		struct foodex_user_t user;
		struct foodex_dasher_t dasher;
		struct foodex_restaurant_t restaurant;
		struct foodex_order_t order;
	} data;
};

#endif // FOODEX_TYPES_H
