#include "Ingredient.h"
#include "SDLGame.h"
#include "SDL_macros.h"

void Ingredient::update() {
	pos_ = pos_ + vel_;
}

void Ingredient::render() const {
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	texture_->render(rect); //Cambiar si los ingredientes vienen todos en una misma textura para usar el clip
}

//Si colisiona en horizontal; llamado por game manager
void Ingredient::onCollisionX() {
	vel_ = Vector2D(-vel_.getX(), SDLGame::instance()->getRandGen()->nextInt(-maxVel_, maxVel_));
}

//Si colisiona en vertical; llamado por game manager
void Ingredient::onCollisionY() {
	vel_ = Vector2D(SDLGame::instance()->getRandGen()->nextInt(-maxVel_, maxVel_), -vel_.getY());
}

//Actualiza vel a la direccion contraria si esta dentro del rango; cpos: posicion del personaje
void Ingredient::escape(Vector2D cpos) {
	//Si escapeRad es para todos el mismo se pone en los personajes y se pasa como parametro
	if (pos_.getX() - cpos.getX() < escapeRadius_ && pos_.getY() - cpos.getY() < escapeRadius_)
		vel_ = pos_ - cpos;
}

void Ingredient::destroy(Resources::UtensilType utensilio)
{
	ingredientPool_->deleteIngredient(it_);
}
