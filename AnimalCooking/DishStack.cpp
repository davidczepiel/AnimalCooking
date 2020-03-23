#include "DishStack.h"
#include"Entity.h"

DishStack::DishStack(int maxDishes_,Transport* t1_,Transport* t2_,EntityManager* mng_) : Entity(SDLGame::instance(), mng_), Interactive(t1_,t2_),maxDishes(maxDishes_)
{

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

void DishStack::action1(int id)
{
	
	if(id==0)
	{		
		if (player1_->getObjectInHands() == nullptr)  player1_->pick(addNewDish(Vector2D(), player1_, player2_),Resources::PickableType::Dish);
		else if(player1_->getObjectTypeInHands()==Resources::PickableType::Dish) 
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			player1_->drop(false);
			removeDish(d);
			
		}
	}
	else 
	{
		if (player2_->getObjectInHands() == nullptr)  player2_->pick(addNewDish(Vector2D(), player1_, player2_), Resources::PickableType::Dish);
		else if (player2_->getObjectTypeInHands() == Resources::PickableType::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			player2_->drop(false);
			removeDish(d);
		}
	}
}