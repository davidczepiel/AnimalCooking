#include "DishMotion.h"
#include "Entity.h"

DishMotion::DishMotion() :Component(ecs::DishMotion)
{

}

void DishMotion::init()
{
	dp = GETCMP1_(DishPool);
}

void DishMotion::update()
{	
	vector<Dish*> d = dp->getDishes();

	for (auto it = d.begin(); it != d.end(); it++)
	{
		(*it)->update();
	}	
}