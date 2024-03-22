#ifndef ACCOUNT_H
#define ACCOUNT_H

int authenticate(string phone, string password);

struct foodex_user_t getUserInfo(int user_id);
int setUserInfo(struct foodex_user_t user);

#endif //ACCOUNT_H
