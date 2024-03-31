#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <mysql.h>

#include "dbtypes.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "FoodEx"

char* db_read_password(MYSQL *con, char password[], char phone[]);

void db_create_user(MYSQL *con, struct user_t);
//struct user_t db_read_user(char phone[]);
//void db_update_user(struct user_t);

//void db_create_menu_list(struct restaurant_t);
//struct restaurant_t db_read_menu_list(int restaurant_id);
//void db_update_menu_list(struct restaurant_t);

//void db_create_order(struct order_t);
//struct user_t db_read_order(int order_id);
//void db_update_order(struct order_t);


#endif //DBCONNECTOR_H
