#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

int password_hash(const char *password, char *hashed);
int password_verify(const char *hashed, const char *password);
int user_register(const char* username, const char *password);
int user_login(const char *username, const char *password, char *token);

#endif //AUTHORIZATION_H
