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
Dish* DishStack::addNewDish(Vector2D pos,Transport* t1,Transport* t2)
{
	if (dishPool->getNumDishes() < maxDishes)
	{
		Dish* d = new Dish(pos,t1,t2);
		d->setPos(pos);
		d->setSize(Vector2D(100, 50));
		d->setSpeed(Vector2D());
		dishPool->addDish(d);	
		
		return d;
	}
	else return nullptr;
}

void DishStack::removeDish(Dish* d)
{
	if(d!=nullptr && dishPool->getNumDishes()>0)dishPool->removeDish(d);
}