#pragma once
#include "Component.h"
#include "ObjectPool.h"
class Food;

class FoodPool : public Component
{
public:
	FoodPool();
	virtual ~FoodPool();

	void AddFood(Food* food);
	void RemoveFood(std::vector<Food*>::iterator it);

	vector<Food*>& getPool();

private:
	vector<Food*> foods_;
};

