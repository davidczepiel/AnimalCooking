#include "FoodPool.h"
#include "Food.h"

FoodPool::FoodPool() : Component(ecs::FoodPool)
{

}

vector<Food*>* FoodPool::getPool()
{
	return &foods_;
}

void FoodPool::AddFood(Food* food)
{
	if (food != nullptr) {
		food->setFoodPool(this);
		foods_.push_back(food);
	}
}
