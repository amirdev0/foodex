#ifndef ACCOUNT_API_H
#define ACCOUNT_API_H

int user_auth(string phone, string password);

struct foodex_user_t user_get_info(int user_id);
int user_set_info(struct foodex_user_t user);

#endif //ACCOUNT_API_H