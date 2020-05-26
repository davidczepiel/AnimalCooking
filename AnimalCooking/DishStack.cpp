#include "DishStack.h"
#include "DishStackViewer.h"
#include "GameConfig.h"
#include "GPadController.h"
#include "Dish.h"

DishStack::DishStack(Vector2D pos, int maxDishes_, Transport* t1_, Transport* t2_, EntityManager* mng_, DishPool* dp, FoodPool* fp) : 
	Entity(SDLGame::instance(), mng_), Interactive(t1_, t2_,nullptr), maxDishes(maxDishes_), dishPool(dp),foodPool(fp), dishSize_()
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
		Dish* d = new Dish(pos, player1_, player2_, config::DISH_MAX_INGR, foodPool);
		d->setPos(pos);
		d->setSize(dishSize_);
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
		if (d->isEmpty())
		{
			player->drop(false);
			removeDish(d);
					SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::DropDish, 0);
		}
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
	if (!SDLGame::instance()->getOptions().showKeyToPress)
		return;

	if (id == Resources::Player::Player1)
	{
		if (player1_->getObjectInHands() == nullptr || player1_->getObjectTypeInHands() == Resources::PickableType::Food) {	
			if (GPadController::instance()->playerControllerConnected(id))
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[0].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[0].PICKUP));
		}
		else if (player1_->getObjectTypeInHands() == Resources::PickableType::Dish && static_cast<Dish*>(player1_->getObjectInHands())->isEmpty()) {
			if (GPadController::instance()->playerControllerConnected(id))
				SDLGame::instance()->renderFeedBack(position_, "Leave it", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[0].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Leave it", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[0].PICKUP));
		}
	}
	else
	{
		if (player2_->getObjectInHands() == nullptr || player2_->getObjectTypeInHands() == Resources::PickableType::Food) {
			if (GPadController::instance()->playerControllerConnected(id))
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[1].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[1].PICKUP));
		}
		else if (player2_->getObjectTypeInHands() == Resources::PickableType::Dish && static_cast<Dish*>(player2_->getObjectInHands())->isEmpty()) {
			if (GPadController::instance()->playerControllerConnected(id))
				SDLGame::instance()->renderFeedBack(position_, "Leave it", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[1].PICKUP));
			else
				SDLGame::instance()->renderFeedBack(position_, "Leave it", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[1].PICKUP));
		}
	}
}

