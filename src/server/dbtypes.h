#ifndef TYPES_H
#define TYPES_H

#define MAXSIZE 255
#define STRSIZE 64

struct user_t {
	int id;
	char phone[STRSIZE];
	char password[STRSIZE];
	enum user_type_e {
		Customer,
		Dasher,
		Restaurant
	} type;
	char name[STRSIZE];
	char email[STRSIZE];
	char address[STRSIZE];
	char image[MAXSIZE];
};

struct dasher_t {
	struct user_t user;
	struct delivery_t {		
		char delivery_type[STRSIZE];
	} delivery;
};

struct restaurant_t {
	struct user_t user;
	struct menu_t {
		int meal_count;
		struct meal_t {
			int id;
			char name[STRSIZE];
			int price;
			char image[MAXSIZE];
		} meal[MAXSIZE];
	} menu;
};

struct order_t {
	int id;
	int customer_id;
	char opened_time[STRSIZE];
	char closed_time[STRSIZE];
	enum status_e {
		Placed,
		Preparing,
		Delivering,
		Finished
	} status;
	struct food_t {
		int restaurant_id;
		int unit_count;
		struct unit_t {
			int meal_id;
			int quantity;
		} unit[MAXSIZE];
	} food;
	struct shipping_t {
		int dasher_id;
		char customer_address[STRSIZE];
		char restaurant_address[STRSIZE];
		char shipping_type[STRSIZE];
	} shipping;
};

#endif //TYPES_H
