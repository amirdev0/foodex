int main (int argc, char **argv)
{
	MYSQL *con = foodle_db_init();
	// How to get menu:
	// struct foodle_meal_t *menu = foodle_db_get_menu(con, 239);
	// struct foodle_meal_t *ptr;
	// for (ptr = menu; ptr->ID != 0; ptr++) {
	// 	printf("%d, %s, %f, %s\n", ptr->ID, ptr->name, ptr->price, ptr->image_path);
	// }
	// free(menu);
	// mysql_close(con);

	struct foodle_meal_t meal = {
		.ID = 414,
		.name = "Pizza but changed",
		.image_path = "Hello",
		.price = 91.91,
	};

	// int r = foodle_db_update_meal_bystruct(con, &meal);
	// struct foodle_meal_t newmeal = foodle_db_get_meal_byid(con, 414);
	// printf("%d, %s, %f, %s\n", meal.ID, meal.name, meal.price, meal.image_path);
	// printf("%d\n", r);
	// printf("%d, %s, %f, %s\n", newmeal.ID, newmeal.name, newmeal.price, newmeal.image_path);

	//int r = foodle_db_delete_meal_byid(con, 414);


	// struct foodle_user_t *rests = foodle_db_get_restaurants(con);
	// struct foodle_user_t *ptr;
	// printf("kffk");
	// for (ptr = rests; ptr->ID != 0; ptr++) {
	// 	printf("'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'\n)", ptr->name, ptr->phone, ptr->email, ptr->password, ptr->address, ptr->region, ptr->image_path, ptr->delivery_type);
	// }

	exit(0);
}

