#pragma once
#include "Component.h"
#include "ObjectPool.h"
class Food;

class FoodPool : public Component
{
public:
	FoodPool();
	vector<Food*>* getPool();
	void AddFood(Food* food);
private:
	vector<Food*> foods_;
};

