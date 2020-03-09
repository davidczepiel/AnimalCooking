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

Dish* DishStack::getDish()
{
	if (dishPool->getNumDishes() < maxDishes)
	{
		Dish* d = new Dish();
		dishPool->addDish(d);
		cout << "Creado nuevo plato"<<dishPool->getNumDishes()<<endl;
		
		return d;
	}
	else return nullptr;
}

void DishStack::removeDish(Dish* d)
{
	if(d!=nullptr && dishPool->getNumDishes()>0)dishPool->removeDish(d);
	cout << "Plato a la mierda" << dishPool->getNumDishes() << endl;
}