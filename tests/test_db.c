//gcc test_db.c -o test_db $(pkg-config --cflags --libs mysqlclient)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "FoodEx"

int main(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "ERR, Failed to initialize connection: %s\n", mysql_error(con));
		exit(1);
  	}
  	printf("OK, Initialized connection\n");
  	
	if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
		fprintf(stderr, "ERR, Failed to establish connection: %s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
  	printf("OK, Established connection to database\n");
  	
	char query[200] = { 0 };
	sprintf(query, "SELECT * FROM user");
	if (mysql_query(con, query)) {
		fprintf(stderr, "ERR, Failed to execute query: %s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	printf("OK, Queried database with statement\n");
	
	MYSQL_RES *res = mysql_store_result(con);
	if (res == NULL) {
		fprintf(stderr, "ERR, Failed to store result: %s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	printf("OK, Stored result of query\n");
	
	printf("\nPrinting result of query:\n");
	int num_fields = mysql_num_fields(res);
	
	MYSQL_FIELD *field;
	while (field = mysql_fetch_field(res))
		printf("%s\t", field->name);
	printf("\n");
  
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		for (int i = 0; i < num_fields; i++)
			printf("%s\t", row[i] ? row[i] : "NULL");
		printf("\n");
		break; //print only first row
	}
	
	mysql_free_result(res);
	
	mysql_close(con);

	return 0;
}
