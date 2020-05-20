#include "FoodGiver.h"
#include "Food.h"
#include "Dish.h"
#include "GPadController.h"


//-----------------------------
RiceGiver::RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Arroz);
}

void RiceGiver::action1(int player) {

	if (player == Resources::Player::Player1)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);

		if(player1_->getObjectInHands() == nullptr) player1_->pick(f, Resources::PickableType::Food);
		else if (player1_->getObjectTypeInHands()==Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}

	}
	else if (player == Resources::Player::Player2 ) {
		Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);

		if (player2_->getObjectInHands() == nullptr)player2_->pick(f, Resources::PickableType::Food);
		else if (player2_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}
}

//-----------------------------
BreadBurgerGiver::BreadBurgerGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panera);
}

void BreadBurgerGiver::action1(int player) {
	if (player == Resources::Player::Player1)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::BreadBurger, position_);

		if (player1_->getObjectInHands() == nullptr)player1_->pick(f, Resources::PickableType::Food);
		else if (player1_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}
	else if (player == Resources::Player::Player2) {
		Food* f = gameControl_->newFood(Resources::FoodType::BreadBurger, position_);

		if (player2_->getObjectInHands() == nullptr)player2_->pick(f, Resources::PickableType::Food);
		else if (player2_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}

}

//-----------------------------
BreadHotDogGiver::BreadHotDogGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panera);
}

void BreadHotDogGiver::action1(int player) {
	if (player == Resources::Player::Player1)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::BreadHotDog, position_);

		if (player1_->getObjectInHands() == nullptr) player1_->pick(f, Resources::PickableType::Food);
		else if (player1_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			d->addFood(f);
		}
	}
	else if (player == Resources::Player::Player2) 
	{
		Food* f = gameControl_->newFood(Resources::FoodType::BreadHotDog, position_);

		if (player2_->getObjectInHands() == nullptr) player2_->pick(f, Resources::PickableType::Food);
		else if (player2_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}

}
//-----------------------------

DoughGiver::DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::EncimeraMasa);
}

void DoughGiver::action1(int player) {
	if (player == Resources::Player::Player1)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);

		if (player1_->getObjectInHands() == nullptr) player1_->pick(f, Resources::PickableType::Food);
		else if (player1_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}
	else if (player == Resources::Player::Player2) {

		Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);

		if (player2_->getObjectInHands() == nullptr) player2_->pick(f, Resources::PickableType::Food);
		else if (player2_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}

}

//-----------------------------
DressingGiver::DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Aceite);
}

void DressingGiver::action1(int player) {
	if (player == Resources::Player::Player1)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);

		if (player1_->getObjectInHands() == nullptr) player1_->pick(f, Resources::PickableType::Food);
		else if (player1_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player1_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}
	else if (player == Resources::Player::Player2) {

		Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);

		if (player2_->getObjectInHands() == nullptr) player2_->pick(f, Resources::PickableType::Food);
		else if (player2_->getObjectTypeInHands() == Resources::Dish)
		{
			Dish* d = static_cast<Dish*>(player2_->getObjectInHands());
			d->addFood(f);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
		}
	}

}

void FoodGiver::feedback(int player)
{
	if (!SDLGame::instance()->getOptions().showKeyToPress)
		return;

	bool render = false;
	if (player == Resources::Player::Player1 && (player1_->getObjectInHands() == nullptr || player1_->getObjectTypeInHands() == Resources::PickableType::Dish)) render = true;
	if (player == Resources::Player::Player2 && (player2_->getObjectInHands() == nullptr || player2_->getObjectTypeInHands() == Resources::PickableType::Dish)) render = true;

	if (render) {
		if (GPadController::instance()->playerControllerConnected(player))
			SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[player].PICKUP));
		else
			SDLGame::instance()->renderFeedBack(position_, "Pick up", SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[player].PICKUP));
	}
}
