#include "DishStack.h"
#include "DishStackViewer.h"


DishStack::DishStack(Vector2D pos, int maxDishes_, Transport* t1_, Transport* t2_, EntityManager* mng_, DishPool* dp, FoodPool* fp) : Entity(SDLGame::instance(), mng_), Interactive(t1_, t2_,nullptr), maxDishes(maxDishes_), dishPool(dp),foodPool(fp)
{
	position_ = pos;
	size_ = Vector2D(128, 128);

	addComponent<DishStackViewer>(this);
}



//A�ade un plato al vector de dishes de la DishPool y lo devuelve
Dish* DishStack::addNewDish(Vector2D pos)
{
	if (dishPool->getNumDishes() < maxDishes)
	{
		Dish* d = new Dish(pos, player1_, player2_,5,foodPool);
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
	if (d != nullptr && dishPool->getNumDishes() > 0)dishPool->removeDish(d);
}

void DishStack::action1(int id)
{
	Transport* player = nullptr;
	if (id == Resources::Player::Player1)
	{
		player = player1_;
	}
	else if (id == Resources::Player::Player2)
		player = player2_;

	if (player->getObjectInHands() == nullptr)  player->pick(addNewDish(Vector2D(position_.getX() + (size_.getX() / 4), position_.getY() + (size_.getY() / 2))), Resources::PickableType::Dish);
	else if (player->getObjectTypeInHands() == Resources::PickableType::Dish)
	{
		Dish* d = static_cast<Dish*>(player->getObjectInHands());
		player->drop(false);
		removeDish(d);
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::DropDish, 0);

	}
	else if (player->getObjectTypeInHands() == Resources::PickableType::Food) {
		Dish* d = addNewDish(Vector2D(position_.getX() + (size_.getX() / 4), position_.getY() + (size_.getY() / 2)));
		d->addFood(static_cast<Food*>(player->getObjectInHands()));
		player->drop(false);
		player->pick(d, Resources::PickableType::Dish);
	}
}

void DishStack::feedback(int id)
{
	SDL_Rect r = RECT(position_.getX() + 50, position_.getY() + 50, 128, 32);

	if (id == Resources::Player::Player1)
	{
		if (player1_->getObjectInHands() == nullptr) feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Coger);
		else if (player1_->getObjectTypeInHands() == Resources::PickableType::Dish) feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Dejar);
	}
	else
	{
		if (player2_->getObjectInHands() == nullptr) feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Coger);
		else if (player2_->getObjectTypeInHands() == Resources::PickableType::Dish) feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Dejar);
	}

	if(feedbackVisual_ !=nullptr) feedbackVisual_->render(r);
	feedbackVisual_ = nullptr;
	
}
