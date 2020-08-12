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
		if(lastVel_.getX()<0) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 1, 0,SDL_FLIP_HORIZONTAL);
		else texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 1, 0); 		
	}
	else if (state == IngredientState::Walking || state == IngredientState::Escaping) 	
	{ 
		if(vel_.getX()<0) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 0, 0,SDL_FLIP_HORIZONTAL);
		else texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 0, 0); 
	}
}

//Si colisiona en horizontal; llamado por game manager
void Ingredient::onCollisionX() {

}

//Si colisiona en vertical; llamado por game manager
void Ingredient::onCollisionY() {
	
}

void Ingredient::destroy()
{
	ingredientPool_->deleteIngredient(it_);
}
