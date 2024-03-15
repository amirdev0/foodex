#ifndef FOODEX_TYPES_H
#define FOODEX_TYPES_H

#define str(x) #x
#define MAXSIZE 255

typedef char string[MAXSIZE];

struct foodex_user_t {
	int id;
	string name;
	string password;
	enum foodex_user_type_e {
		Restaurant,
		Customer,
		Dasher
	} type;
	string email;
	string phone;
	string address;
	string region;
	string image_path;
	string delivery_type;
};

struct foodex_meal_t {
	int id;
	string name;
	float price;
	string image_path;
};

struct foodex_menu_t {
	struct foodex_meal_t meal[MAXSIZE];
};

struct foodex_restaurant_t {
	int id;
	string name;
	struct foodex_menu_t menu;
	string address;
	string region;
	string image_path;
};

struct foodex_item_t {
	struct foodex_meal_t meal;
	int quantity;
	float net_price;
};

struct foodex_cart_t {
	struct foodex_item_t item[MAXSIZE];
	int total_price;
};

struct foodex_delivery_t {
	int order_id;
	string restaurant_address;
	string customer_address;
};

struct foodex_order_t {
	int id;
	int customer_id;
	int restaurant_id;
	int dasher_id;
	enum foodex_order_status_e {
		Pending,
		Confirmed,
		Preparing,
		Delivering,
		Finished
	} status;
	//string status;
	string address;
	string date;
	struct foodex_cart_t cart;
};

struct foodex_event_t {
	enum foodex_event_type_e {
		AUTHENTICATE_USER,
		ADD_USER_INFO,
		GET_USER_INFO,

		ADD_MEAL,
		GET_MEAL,
		UPDATE_MEAL,
		DELETE_MEAL,

		GET_RESTAURANT_LIST,
		GET_MENU,
		ORDER_CART,
	
		GET_ORDER_LIST,
		SELECT_ORDER,
		FINISH_ORDER,

		GET_DELIVERY_LIST,
		CHOOSE_DELIVERY,
		WITHDRAW_DELIVERY,
		FINISH_DELIVERY
	} type;
	
	union foodex_data_u {
		struct foodex_user_t user;
		struct foodex_menu_t menu;
		struct foodex_meal_t meal;
		struct foodex_restaurant_t restaurant;
		struct foodex_restaurant_t restaurant_list[MAXSIZE];
		struct foodex_order_t order;
		struct foodex_order_t order_list[MAXSIZE];
		struct foodex_delivery_t delivery;
		struct foodex_delivery_t delivery_list[MAXSIZE];
	} data;
};

#endif // FOODEX_TYPES_H
