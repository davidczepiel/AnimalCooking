#include "Ingredient.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "GameConfig.h"

void Ingredient::update() {
	pos_ = pos_ + vel_;
}

void Ingredient::render() const {
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	//int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows()))

	if (state == IngredientState::Idle) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())),1, 0);
	else if(state == IngredientState::Walking || state == IngredientState::Escaping) texture_->renderFrame(rect, int(((SDLGame::instance()->getTime() / config::ANIM_SPEED) % texture_->getNumRows())), 0, 0);

	//texture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip
}

//Si colisiona en horizontal; llamado por game manager
void Ingredient::onCollisionX() {

}

//Si colisiona en vertical; llamado por game manager
void Ingredient::onCollisionY() {
	
}

void Ingredient::destroy(Resources::UtensilType utensilio)
{
	ingredientPool_->deleteIngredient(it_);
}
