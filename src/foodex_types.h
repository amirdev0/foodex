#ifndef FOODEX_TYPES_H
#define FOODEX_TYPES_H

#define STRSIZE 64
#define MAXSIZE 255

typedef char string[STRSIZE];
typedef char path[MAXSIZE];

enum user_type_e {
	CUST,
	DASH,
	REST
};
	
enum foodex_event_type_e {
	AUTHENTICATION,
	USER_GET_INFO,
	USER_SET_INFO,
	DASH_GET_INFO,
	DASH_SET_INFO,
	REST_GET_INFO,
	REST_SET_INFO,
	REST_GET_LIST,
	ORDER_GET_INFO,
	ORDER_SET_INFO,
	ORDER_GET_LIST,
};

enum foodex_event_result_e {
	NONE,
	FAIL,
	SUCCESS
};
	
struct foodex_event_t {
	enum foodex_event_type_e type;
	enum foodex_event_result_e result;
	union foodex_data_u {
		struct foodex_atomic_t {
			int order_id;
			int customer_id;
			int dasher_id;
			int restaurant_id;
			int meal_id;
			int quantity;
			int price;
			int order_status;
			string phone;
			string password;
			string user_name;
			string user_email;
			string customer_address;
			string dasher_address;
			string restaurant_address;
			string delivery_type;
			string meal_name;
			path meal_image;
			path user_image;
		} atomic;
		union foodex_array_t {
			struct foodex_menu_t {
				struct foodex_meal_t {
					int id;
					string name;
					int price;
					path image;
				} meal[MAXSIZE];
			} menu;
			struct foodex_restaurant_t {
				int id;
				string name;
				string address;
				path image;
			} restaurant[MAXSIZE];
			struct foodex_delivery_t {
				int order_id;
				string restaurant_address;
				string customer_address;
			} delivery[MAXSIZE];
			struct foodex_draft_t {
				int order_id;
				struct foodex_item_t {
					int id;
					string name;
					int quantity;
				} item[MAXSIZE];
			} draft;
		} array;
	} data;
};

#endif //FOODEX_TYPES_H
