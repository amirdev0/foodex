#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "foodex_types.h"
#include "data_transfer.h"
#include "restaurant.h"

extern struct foodex_event_t event;
extern union foodex_data_u data;

//CREATE_MEAL,
//READ_MEAL,
//UPDATE_MEAL,
//DELETE_MEAL,

int addMeal(const char *meal_name, const char *price, const char *time, const char *path, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = ADD_MEAL;
	event.data.restaurant.id = restaurantID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = atof(price);
	strcpy(event.data.meal.image_path, path);
	char arr[MAXSIZE]; strcpy(arr, time);

	return transfer(&event, &data);
}

int getMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_MEAL;
	event.data.restaurant.id = restaurantID;
	event.data.meal.id = mealID;

	return transfer(&event, &data);
}

int updateMeal(int mealID, char* meal_name, float price, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = UPDATE_MEAL;
	event.data.restaurant.id = restaurantID;
	event.data.meal.id = mealID;
	strcpy(event.data.meal.name, meal_name);
	event.data.meal.price = price;
	
	return transfer(&event, &data);
}

int deleteMeal(int mealID, int restaurantID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = DELETE_MEAL;
	event.data.restaurant.id = restaurantID;
	event.data.meal.id = mealID;

	return transfer(&event, &data);
}

int getOrderList(void)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = GET_ORDER_LIST;

	return transfer(&event, &data);
}

int selectOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = SELECT_ORDER;
	event.data.order.id = orderID;
	//strcpy(event.data.order.status, str(Preparing));

	return transfer(&event, &data);
}

int finishOrder(int orderID)
{
	memset(&event, 0, sizeof(event));
	memset(&data, 0, sizeof(data));
	
	event.type = FINISH_ORDER;
	event.data.order.id = orderID;
    
	return transfer(&event, &data);
}

