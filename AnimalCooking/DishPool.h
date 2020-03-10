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

	 //Metodo auxiliar para meter platos llamar al de DishStack
	void addDish(Dish* d);
	void removeDish(Dish* d);
	int getNumDishes() { return dishes_.size(); }
	inline list<Dish*> getDishes() { return dishes_; }

private:
	list<Dish*> dishes_;
};
