#include "FoodGiver.h"
#include "Food.h"



//-----------------------------
RiceGiver::RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Arroz);
}

void RiceGiver::action1(int player) {

	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);
		player1_->pick(f, Resources::PickableType::Food);
	}
	else if (player2_->getObjectInHands() == nullptr) {
		Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);
		player2_->pick(f, Resources::PickableType::Food);
	}


}

//-----------------------------
BreadBurgerGiver::BreadBurgerGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panera);
}

void BreadBurgerGiver::action1(int player) {
	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::BreadBurger, position_);
		player1_->pick(f, Resources::PickableType::Food);
	}
	else if (player2_->getObjectInHands() == nullptr) {
		Food* f = gameControl_->newFood(Resources::FoodType::BreadBurger, position_);
		player2_->pick(f, Resources::PickableType::Food);
	}

}

//-----------------------------
BreadHotDogGiver::BreadHotDogGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Panera);
}

void BreadHotDogGiver::action1(int player) {
	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::BreadHotDog, position_);
		player1_->pick(f, Resources::PickableType::Food);
	}
	else if (player2_->getObjectInHands() == nullptr) {
		Food* f = gameControl_->newFood(Resources::FoodType::BreadHotDog, position_);
		player2_->pick(f, Resources::PickableType::Food);
	}

}
//-----------------------------

DoughGiver::DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Pan);
}

void DoughGiver::action1(int player) {
	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);
		player1_->pick(f, Resources::PickableType::Food);
	}
	else if (player2_->getObjectInHands() == nullptr) {
		Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);
		player2_->pick(f, Resources::PickableType::Food);
	}

}

//-----------------------------
DressingGiver::DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Aceite);
}

void DressingGiver::action1(int player) {
	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr)
	{
		Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);
		player1_->pick(f, Resources::PickableType::Food);
	}
	else if (player2_->getObjectInHands() == nullptr) {
		Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);
		player2_->pick(f, Resources::PickableType::Food);
	}

}

void FoodGiver::feedback(int player)
{
	bool render = false;
	if (player == Resources::Player::Player1 && player1_->getObjectInHands() == nullptr) render = true;
	if (player == Resources::Player::Player2 && player2_->getObjectInHands() == nullptr) render = true;

	if (render) {
		SDL_Rect r = RECT(position_.getX() + 50, position_.getY() + 50, 128, 32);
		feedbackVisual_->render(r);
	}
}
