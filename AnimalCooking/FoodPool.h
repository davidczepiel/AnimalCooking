#pragma once
#include "Component.h"
#include "ObjectPool.h"
class Food;

class FoodPool : public Component
{
public:
	FoodPool();
	virtual ~FoodPool();

	vector<Food*>* getPool();
	void AddFood(Food* food);
	void RemoveFood(std::vector<Food*>::iterator it);
private:
	vector<Food*> foods_;
};

