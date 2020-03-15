#include "FoodPool.h"
#include "Food.h"

FoodPool::FoodPool() : Component(ecs::FoodPool)
{
	foods_ = vector<Food*>();
}

vector<Food*>* FoodPool::getPool()
{
	return &foods_;
}

void FoodPool::AddFood(Food* food)
{
	if (food != nullptr) {
		foods_.push_back(food);
		food->setFoodPool(this, --foods_.end());
	}
}

void FoodPool::RemoveFood(std::vector<Food*>::iterator it)
{
	delete* it;
	foods_.erase(it);
}
