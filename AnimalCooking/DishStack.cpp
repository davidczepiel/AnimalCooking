#include "DishStack.h"
#include "DishStackViewer.h"

DishStack::DishStack(Vector2D pos,int maxDishes_,Transport* t1_,Transport* t2_,EntityManager* mng_, DishPool* dp) : Entity(SDLGame::instance(), mng_), Interactive(t1_,t2_),maxDishes(maxDishes_),dishPool(dp)
{
	position_ = pos;
	size_ = Vector2D(100, 100);

	addComponent<DishStackViewer>(this);
}



//A�ade un plato al vector de dishes de la DishPool y lo devuelve
Dish* DishStack::addNewDish(Vector2D pos)
{
	if (dishPool->getNumDishes() < maxDishes)
	{
		Dish* d = new Dish(pos,player1_,player2_);
		d->setPos(pos);
		d->setSize(Vector2D(75, 30));
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
	
	if(id==Resources::Player::Player1)
	{				
		if (player1_->getObjectInHands() == nullptr)  player1_->pick(addNewDish(Vector2D(position_.getX()+(size_.getX()/4),position_.getY()+(size_.getY()/2))),Resources::PickableType::Dish);
		else if(player1_->getObjectTypeInHands()==Resources::PickableType::Dish) 
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			player1_->drop(false);
			removeDish(d);
			
		}
	}
	else 
	{
		if (player2_->getObjectInHands() == nullptr)  player2_->pick(addNewDish(Vector2D()), Resources::PickableType::Dish);
		else if (player2_->getObjectTypeInHands() == Resources::PickableType::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			player2_->drop(false);
			removeDish(d);
		}
	}
}