#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include "foodex_types.h"
#include "mysql.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_DATABASE "FoodEx"

/*
* @desc Function to initialize database connection
* @return A pointer to MYSQL connection
*/
MYSQL*
db_init(
	void
);

/*
* @desc Get user by phone
* @param[in] MYSQL *con - connection to database
* @param[in] char *phone - phone number of user
* @return pointer to foodle_user_t actual or user with userID = -1 if not found
*/
struct foodex_user_t*
db_get_user_by_phone(
	MYSQL *con, 
	char *phone
);

/*
* @desc Get user by ID
* @param[in] MYSQL *con - connection to database
* @param[in] int userID - ID of user
* @return pointer to foodle_user_t actual or user with userID = -1 if not found
*/
struct foodex_user_t*
db_get_user_by_id(
	MYSQL *con,
	int userID
);

int
db_add_user(
	MYSQL *con, 
	struct foodex_user_t *user
);

/*
* @desc Function to add meal
* @param[in] MYSQL *con - connection to database
* @param[in] struct foodle_meal_t *meal - meal to add
* @param[in] int restaurantID - ID of restaurant adding meal
*/
int
db_add_meal(
	MYSQL *con, 
	struct foodex_meal_t *meal,
	int restaurantID
);

int
db_update_meal_by_struct(
	MYSQL *con,
	struct foodex_meal_t *meal
);

int
db_delete_meal_by_id(
	MYSQL *con,
	int id
);

struct foodex_meal_t*
db_get_meal_by_id(
	MYSQL *con,
	int id
);

struct foodex_restaurant_t*
db_get_restaurants(
    MYSQL* con
);

struct foodex_menu_t*
db_get_menu(
	MYSQL *con,
	int id
);

#endif //DBCONNECTOR_H
