#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_DATABASE "FoodEx"

/*
* @desc Function to initialize database connection
* @return A pointer to MYSQL connection
*/
MYSQL*
db_init(
	void
);

char* db_read_password(char *phone);
void db_create_user(struct user_t);
struct user_t db_read_user(char *phone);
void db_create_menu_list(struct restaurant_t);
void db_create_order(int cust_id);


#endif //DBCONNECTOR_H
