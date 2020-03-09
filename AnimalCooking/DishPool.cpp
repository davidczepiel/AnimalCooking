#include "DishPool.h"

DishPool::DishPool() :Component(ecs::DishPool)
{
}

void DishPool::addDish(Dish* d)
{
	dishes_.push_back(d);
}

void DishPool::removeDish(Dish* d)
{
	if(!dishes_.empty())dishes_.remove(d);	
}