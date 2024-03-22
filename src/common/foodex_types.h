#ifndef FOODEX_TYPES_H
#define FOODEX_TYPES_H

#define STRSIZE 64
#define MAXSIZE 256

typedef char string[STRSIZE];
typedef char path[MAXSIZE];

enum foodex_event_type_e {
	AUTHENTICATION,
	GET_USER_INFO,
	SET_USER_INFO,
	GET_DASH_INFO,
	SET_DASH_INFO,
	GET_REST_LIST,
	GET_REST_INFO,
	SET_REST_INFO,
	GET_ORDER_LIST,	
	GET_ORDER_INFO,
	SET_ORDER_INFO,
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
			struct foodex_meal_t {
				int id;
				string name;
				int price;
				path image;
			} meal[MAXSIZE];
			struct foodex_restaurant_t {
				int id;
				string name;
				string address;
				path image;
			} restaurant[MAXSIZE];
		} array;
	} data;
};

#endif // FOODEX_TYPES_H
