#include "FoodPool.h"
#include "Food.h"

FoodPool::FoodPool() : Component(ecs::FoodPool)
{
	foods_ = vector<Food*>();
	foods_.reserve(40);
}

FoodPool::~FoodPool() {
	for (size_t i = 0; i < foods_.size(); i++)
	{
		delete foods_.at(i);
	}
	foods_.clear();
}

vector<Food*>& FoodPool::getPool()
{
	return foods_;
}

void FoodPool::AddFood(Food* food)
{
	if (food != nullptr) {
		foods_.emplace_back(food);
		food->setFoodPool(this, --foods_.end());
	}
}

void FoodPool::RemoveFood(std::vector<Food*>::iterator it)
{
	Food* i = *--foods_.end();
	i->setIt(it);
	iter_swap(it, --foods_.end());
	foods_.pop_back();
}
