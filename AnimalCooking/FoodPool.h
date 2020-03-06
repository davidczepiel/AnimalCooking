#pragma once
#include "ObjectPool.h"
class Food;

class FoodPool : public ObjectPool<Food>
{
private:
	ObjectPool<Food> pool;
};

