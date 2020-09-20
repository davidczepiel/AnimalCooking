#include "Ingredient.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "GameConfig.h"

void Ingredient::update() {
	pos_ = pos_ + vel_;
}

void Ingredient::render() const
{
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	if (state == IngredientState::Idle)
	{
		if (lastVel_.getX() < 0) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 1, 0, SDL_FLIP_HORIZONTAL);
		else texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 1, 0);
	}
	else if (state == IngredientState::Walking || state == IngredientState::Escaping || state==IngredientState::WallScaping)
	{
		if (vel_.getX() < 0) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 0, 0, SDL_FLIP_HORIZONTAL);
		else texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 0, 0);
	}
}

//Si colisiona en horizontal; llamado por game manager
void Ingredient::onCollisionX() {
	Vector2D p1toIngredient((pos_.getX() + (size_.getX() / 2)) - (trPlayer1->getPos().getX() + (trPlayer1->getW() / 2)), 
		(pos_.getY() + (size_.getY() / 2)) - (trPlayer1->getPos().getY() + (trPlayer1->getH() / 2)));
	Vector2D p2toIngredient((pos_.getX() + (size_.getX() / 2)) - (trPlayer2->getPos().getX() + (trPlayer2->getW() / 2)),
		(pos_.getY() + (size_.getY() / 2)) - (trPlayer2->getPos().getY() + (trPlayer2->getH() / 2)));
	/*double angleP1 = atan2(p1toIngredient.getY(), p1toIngredient.getX()) * (180 / M_PI);
	double angleP2 = atan2(p2toIngredient.getY(), p2toIngredient.getX() * (180 / M_PI));*/
	aiIngredient_->NotCorner(p1toIngredient,p2toIngredient, this);
	
}
//Si colisiona en vertical; llamado por game manager
void Ingredient::onCollisionY() {
	onCollisionX();//quiero hacer lo mismo en ambas colisiones
}

void Ingredient::onCollisionXY()
{
	aiIngredient_->Corner(this);
}

void Ingredient::destroy()
{
	ingredientPool_->deleteIngredient(it_);
	
}
