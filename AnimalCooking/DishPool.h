#pragma once
#include "Component.h"
#include <vector>
class Dish;

class DishPool : public Component
{
public:
	DishPool();
	~DishPool() { }

	//Metodo auxiliar para meter platos llamar al de DishStack
	void addDish(Dish* d);
	void removeDish(Dish* d);

	int getNumDishes() { return dishes_.size(); }
	inline vector<Dish*>& getDishes() { return dishes_; }

private:
	vector<Dish*> dishes_;
};
