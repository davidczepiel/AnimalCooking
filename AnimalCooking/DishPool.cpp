#include "DishPool.h"
#include "Dish.h"

DishPool::DishPool() :Component(ecs::DishPool),dishes_()
{
}

void DishPool::addDish(Dish* d)
{	
	if(d!=nullptr)
		dishes_.push_back(d);	
}

void DishPool::removeDish(Dish* d)
{
	if (!dishes_.empty())
	{
       delete d;	
	   dishes_.erase(std::remove(dishes_.begin(),dishes_.end(),d),dishes_.end());
	}	
}