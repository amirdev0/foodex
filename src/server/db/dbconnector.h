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

#endif //DBCONNECTOR_H
