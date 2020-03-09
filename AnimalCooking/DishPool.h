#pragma once
#include "Component.h"
#include <list>
#include"Dish.h"
using namespace std;

class DishPool : public Component
{
public:
	DishPool();
	~DishPool() { }

	void addDish(Dish* d);
	void removeDish(Dish* d);
	int getNumDishes() { return dishes_.size(); }

private:
	list<Dish*> dishes_;
};
