#ifndef USER_API_H
#define USER_API_H

struct user_t {
	int id;
	enum user_type_e {
		Customer,
		Dasher,
		Restaurant
	} type;
	string phone;
	string name;
	string email;
	string address;
	path image;
};

int user_auth(string phone, string password);

struct user_t user_get_info(int user_id);
int user_set_info(struct user_t user);

#endif //USER_API_H
