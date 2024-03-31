#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "dbtypes.h"
#include "dbconnector.h"

char* db_read_password(MYSQL *con, char password[], char phone[])
{
	char query[200] = { 0 };
	sprintf(query, "SELECT password FROM user WHERE phone_number='%s'", phone);
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	
	MYSQL_RES *res = mysql_store_result(con);
	if (res == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	
	MYSQL_ROW row = mysql_fetch_row(res);
	strcpy(password, row[0] ? row[0] : "");
	
	mysql_free_result(res);
	
	return password;
}

void db_create_user(MYSQL *con, struct user_t user)
{
	char query[800] = { 0 };
	sprintf(query, "INSERT INTO user VALUES(NULL, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", user.name, user.phone, user.email, user.password, user.address, "", "Tashkent", user.image, "");
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
}
