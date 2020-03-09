#pragma once
#include "Component.h"
#include "DishPool.h"
class DishStack : public Component
{
public:

	DishStack(int maxDishes_);
	 ~DishStack() { }

	void init() override;
	Dish* getDish();
	void removeDish(Dish* d);

private:
	int maxDishes;
	DishPool* dishPool = nullptr;
};

