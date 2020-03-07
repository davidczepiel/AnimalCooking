#pragma once
#include "Component.h"
#include "ObjectPool.h"
class Food;

enum FoodType {
	SlicedTomato,
	SmashedTomato,
	SlicedLettuce,
	WrongFood,
	RawMeat,
	CookedMeat
};

class FoodPool : public Component
{
public:
	FoodPool();
	vector<Food*>* getPool();
	void AddFood(Food* food);
private:
	vector<Food*> foods_;
};

