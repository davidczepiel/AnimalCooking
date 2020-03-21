#include "FoodGiver.h"
#include "Food.h"

void FoodGiver::render() const {
	SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
	texture_->render(destRect);
}

//-----------------------------
RiceGiver::RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Arroz);
}

void RiceGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);

	if (player == 0)
		player1_->pick(f, Resources::PickableType::Food);
	else
		player2_->pick(f, Resources::PickableType::Food);
}

//-----------------------------
BreadGiver::BreadGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Pan);
}

void BreadGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Bread, position_);

	if (player == 0)
		player1_->pick(f, Resources::PickableType::Food);
	else
		player2_->pick(f, Resources::PickableType::Food);
}

//-----------------------------
DoughGiver::DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Pan);
}

void DoughGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);

	if (player == 0)
		player1_->pick(f, Resources::PickableType::Food);
	else
		player2_->pick(f, Resources::PickableType::Food);
}

//-----------------------------
DressingGiver::DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Aceite);
}

void RiceGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);

	if (player == 0)
		player1_->pick(f, Resources::PickableType::Food);
	else
		player2_->pick(f, Resources::PickableType::Food);
}