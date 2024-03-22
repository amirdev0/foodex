struct user_t {
	int id;
	string phone;
	string password;
	enum user_type_e {
		Customer,
		Dasher,
		Restaurant
	} type;
	string name;
	string email;
	string address;
	path image;
};

struct dasher_t {
	struct user_t user;
	struct delivery_t {		
		string delivery_type;
	} delivery;
};

struct restaurant_t {
	struct user_t user;
	struct menu_t {
		int meal_count;
		struct meal_t {
			int id;
			string name;
			int price;
			path image
		} meal[MAXSIZE];
	} menu;
};

struct order_t {
	int id;
	int customer_id;
	string opened_time;
	string closed_time;
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
		string customer_address;
		string restaurant_address;
		string shipping_type;
	} shipping;
};
