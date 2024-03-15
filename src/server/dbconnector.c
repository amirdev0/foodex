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



struct foodex_user_t* db_get_user_by_phone(MYSQL *con, char *phone)
{
	char query[200];
	struct foodex_user_t *user = malloc(sizeof(struct foodex_user_t));
	if (user == NULL) {
		fprintf(stderr, "[!] Error in memory allocation.\n");
		return NULL;
	}

	sprintf(query, "SELECT * FROM user WHERE phone_number='%s'", phone);
	if (mysql_query(con, query))
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
		fprintf(stderr, "[!] %s\n", mysql_error(con));
		return NULL;
	}

	MYSQL_ROW row = mysql_fetch_row(result);
	if (row == 0) {
		user->id = -1;
		return user;
	}
    
	user->id = atoi(row[0]);
	strcpy(user->name, row[1]);
	strcpy(user->phone, row[2]);
	strcpy(user->email, row[3]);
	strcpy(user->password, row[4]);
	strcpy(user->address, row[5]);
	if (strcmp(row[6], "Restaurant") == 0) user->type = Restaurant;
	if (strcmp(row[6], "Customer") == 0) user->type = Customer;
	if (strcmp(row[6], "Dasher") == 0) user->type = Dasher;
	row[7] && strcpy(user->region, row[7]);
	row[8] && strcpy(user->image_path, row[8]);
	row[9] && strcpy(user->delivery_type, row[9]);       

	return user;
}

struct foodex_user_t* db_get_user_by_id(MYSQL *con, int user_id)
{
	char query[200];
	struct foodex_user_t *user = malloc(sizeof(struct foodex_user_t));
	if (user == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		exit(1);
	}

	sprintf(query, "SELECT * FROM user WHERE user_id='%d'", user_id);
	if (mysql_query(con, query))
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return NULL;
	}

	MYSQL_ROW row = mysql_fetch_row(result);
	if (row == 0) {
		user->id = -1;
		return user;
	}
    
	user->id = atoi(row[0]);
	strcpy(user->name, row[1]);
	strcpy(user->phone, row[2]);
	strcpy(user->email, row[3]);
	strcpy(user->password, row[4]);
	strcpy(user->address, row[5]);
	if (strcmp(row[6], "Restaurant") == 0) user->type = Restaurant;
	if (strcmp(row[6], "Customer") == 0) user->type = Customer;
	if (strcmp(row[6], "Dasher") == 0) user->type = Dasher;
	row[7] && strcpy(user->region, row[7]);
	row[8] && strcpy(user->image_path, row[8]);
	row[9] && strcpy(user->delivery_type, row[9]);       

	return user;
}

int db_add_user(MYSQL *con, struct foodex_user_t *user)
{
	char query[200];

	sprintf(query, "INSERT INTO user VALUES(NULL, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", user->name, user->phone, user->email, user->password, user->address, user_type_etos[user->type], user->region, user->image_path, user->delivery_type);
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return 0;
	}
	
	return 1;
}

int db_add_meal(MYSQL *con, struct foodex_meal_t *meal, int restaurant_id)
{
	char query[200];
	
	sprintf(query, "INSERT INTO menu VALUES(NULL, %d, '%s', %f, '%s')", restaurant_id, meal->name, meal->price, meal->image_path);
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return 0;
	}
	
	return 1;
}

int db_update_meal_by_struct(MYSQL *con, struct foodex_meal_t *meal)
{
	char query[200];
	
	sprintf(query, "UPDATE menu SET item_name='%s', item_price=%f, item_image_path='%s' WHERE menu_id=%d", meal->name, meal->price, meal->image_path, meal->id);
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return 0;
	}
	
	return 1;
}

int db_delete_meal_by_id(MYSQL *con, int id)
{
	char query[200];
	sprintf(query, "DELETE FROM menu WHERE menu_id=%d", id);
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return 0;
	}
	
	return 1;
}

struct foodex_meal_t* db_get_meal_by_id(MYSQL *con, int id)
{
	char query[200];
	struct foodex_meal_t *meal = malloc(sizeof(struct foodex_meal_t));
	if (meal == NULL) {
		fprintf(stderr, "Error in memory allocation.\n");
		return NULL;
	}

	sprintf(query, "SELECT * FROM menu WHERE menu_id=%d", id);
	if (mysql_query(con, query))
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
	  fprintf(stderr, "%s\n", mysql_error(con));
	  return NULL;
	}
	
	MYSQL_ROW row = mysql_fetch_row(result);
	if (row == 0)
    	return NULL;
    
	meal->id = atoi(row[0]);
	strcpy(meal->name, row[2]);
	meal->price = atof(row[3]);
	strcpy(meal->image_path, row[4]);

	return meal;
}

struct foodex_restaurant_t* db_get_restaurants(MYSQL* con)
{
	char query[200];
	struct foodex_restaurant_t *restaurants = malloc(20 * sizeof(struct foodex_restaurant_t));

	strcpy(query, "SELECT * FROM user WHERE user_type='Restaurant'");
	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return NULL;
	}

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);

	MYSQL_ROW row;
	for (int i = 0; (row = mysql_fetch_row(result)) && i < 20; i++) {
		restaurants[i].id = atoi(row[0]);
        strcpy(restaurants[i].name, row[1]);
        strcpy(restaurants[i].address, row[5]);
        strcpy(restaurants[i].region, row[7]);
        strcpy(restaurants[i].image_path, row[8]);
	}

	return restaurants;
}

struct foodex_menu_t* db_get_menu(MYSQL *con, int id)
{
	char query[200];
	struct foodex_menu_t *menu = malloc(sizeof(struct foodex_menu_t));

	sprintf(query, "SELECT * FROM menu WHERE restaurant_id=%d", id);
	if (mysql_query(con, query))
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);

	MYSQL_ROW row;
	for (int i = 0; (row = mysql_fetch_row(result)) && i < 20; i++) {
		menu->meal[i].id = atoi(row[0]);
		strcpy(menu->meal[i].name, row[2]);
		menu->meal[i].price = atof(row[3]);
		strcpy(menu->meal[i].image_path, row[4]);
	}
	
	return menu;
}
