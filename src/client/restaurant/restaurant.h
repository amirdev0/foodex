#ifndef RESTAURANT_H
#define RESTAURANT_H

#define MAXSIZE 256

struct menu_t {
	struct meal_t {
		int id;
		string name;
		int price;
		path image
	} meal[MAXSIZE];
};

struct draft_t {
	int order_id;
	struct item_t {
		int id;
		string name;
		int quantity;
	} item[MAXSIZE];
};

struct menu_t getMenuList(int restaurant_id);
int setMenuList(struct menu_t menu);

int createMeal(struct menu_t *menu, string name, int price, path image);
int updateMeal(struct menu_t *menu, int meal_id, int price, path image);
int deleteMeal(struct menu_t *menu, int meal_id);

struct draft_t getDraftList(int restaurant_id);
int cookDraft(struct draft_t *draft, int restaurant_id);
int cookDraft(struct draft_t *draft, int restaurant_id);

#endif //RESTAURANT_H
