#ifndef USER_API_H
#define USER_API_H

struct user_t;

int user_auth(string phone, string password);

struct user_t user_get_info(int user_id);

int user_set_info(struct user_t user);

#endif //USER_API_H
