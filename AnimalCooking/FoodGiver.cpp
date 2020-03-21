#include "FoodGiver.h"
#include "Food.h"

void FoodGiver::giveFood(int player, Food* f)
{
	if (player == 0)
		player1_->pick(f, Resources::PickableType::Food);
	else
		player2_->pick(f, Resources::PickableType::Food);
}

//-----------------------------
RiceGiver::RiceGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Arroz);
}

void RiceGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Rice, position_);

	giveFood(player, f);
}

//-----------------------------
BreadGiver::BreadGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Pan);
}

void BreadGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Bread, position_);

	giveFood(player, f);
}

//-----------------------------
DoughGiver::DoughGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Pan);
}

void DoughGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::PizzaMass, position_);

	giveFood(player, f);
}

//-----------------------------
DressingGiver::DressingGiver(Vector2D pos, Vector2D size, Transport* p1, Transport* p2, GameControl* gameControl) : FoodGiver(pos, size, p1, p2, gameControl)
{
	texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Aceite);
}

void DressingGiver::action1(int player) {
	Food* f = gameControl_->newFood(Resources::FoodType::Dress, position_);

	giveFood(player, f);
}
