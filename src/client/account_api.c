#include "foodex_types.h"
#include "transmission.h"
#include "account_api.h"

extern int server_sock;

int user_auth(string phone, string password);

struct user_t user_get_info(int user_id);

int user_set_info(struct user_t user);
