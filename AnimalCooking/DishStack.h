#pragma once
#include "Component.h"
#include "DishPool.h"

class DishStack : public Component
{
public:

	DishStack(int maxDishes_);
	 ~DishStack() { }

	void init() override;
	Dish* addNewDish(Vector2D pos, Transport* t1, Transport* t2);
	void removeDish(Dish* d);

private:
	int maxDishes;
	DishPool* dishPool = nullptr;
};

