#include "foodex_types.h"
#include "transmission.h"
#include "user_api.h"

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

extern int server_sock;

int user_auth(string phone, string password)
{
	struct foodex_event_t event = { .type = AUTHENTICATION };
	strncpy(event.data.atomic.phone, phone, STRSIZE);
	strncpy(event.data.atomic.password, password, STRSIZE);
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return event.data.atomic.customer_id;
}

struct user_t user_get_info(int user_id)
{
	struct foodex_event_t event = { .type = GET_USER_INFO };
	event.data.atomic.customer_id = user_id;
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return (struct user_t){ 0 };
	
	struct user_t user;
	user.id = event.data.atomic.customer_id;
	strncpy(user.phone, event.data.atomic.phone, STRSIZE);
	strncpy(user.name, event.data.atomic.user_name, STRSIZE);
	strncpy(user.email, event.data.atomic.user_email, STRSIZE);
	strncpy(user.address, event.data.atomic.customer_address, STRSIZE);
	strncpy(user.image, event.data.atomic.user_image, MAXSIZE);
	event = transmit(event, server_sock);
	
	return user;
}

int user_set_info(struct user_t user)
{
	struct foodex_event_t event = { .type = SET_USER_INFO };
	event.data.atomic.customer_id = user.id;	
	strncpy(event.data.atomic.phone, user.phone, STRSIZE);
	strncpy(event.data.atomic.user_name, user.name, STRSIZE);
	strncpy(event.data.atomic.user_email, user.email, STRSIZE);
	strncpy(event.data.atomic.customer_address, user.address, STRSIZE);
	strncpy(event.data.atomic.user_image, user.image, MAXSIZE);
	event = transmit(event, server_sock);
	
	if (event.result == FAIL)
		return -1;
	
	return 0;	
}
