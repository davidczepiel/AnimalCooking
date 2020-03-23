#include "DishStack.h"
#include"Entity.h"

DishStack::DishStack(int maxDishes_) : Component(ecs::DishStack)
{
	maxDishes = maxDishes_;
}

void DishStack::init()
{
	dishPool = GETCMP1_(DishPool);
}

//Añade un plato al vector de dishes de la DishPool y lo devuelve
Dish* DishStack::addNewDish(Vector2D pos)
{
	/*if (dishPool->getNumDishes() < maxDishes)
	{
		Dish* d = new Dish(pos);
		dishPool->addDish(d);	
		
		return d;
	}
	else*/ return nullptr;
}

void DishStack::removeDish(Dish* d)
{
	if(d!=nullptr && dishPool->getNumDishes()>0)dishPool->removeDish(d);
}