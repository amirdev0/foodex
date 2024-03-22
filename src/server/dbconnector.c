#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>

#include "dbconnector.h"
#include "foodex_types.h"

string user_type_etos[] = {
	"Restaurant",
	"Customer",
	"Dasher"
};

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

MYSQL* db_init(void)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
  	}
	
	if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_DATABASE, 0, NULL, 0) == NULL)
		finish_with_error(con);
    
	printf("Connected to database\n");

	return con;
}
