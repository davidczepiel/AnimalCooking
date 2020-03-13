#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"

class Food : public Pickable 
{
protected:
	Food(Vector2D position, Resources::FoodType type);

	Resources::FoodType type_;

	FoodPool* foodPool_;
	std::vector<Food*>::iterator iterator_;
public:
	void setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it);
	void Destroy();

	Resources::FoodType getType() { return type_; }

	virtual void update(); //Este udate solo actualiza la posicion respecto a la direccion
	virtual void draw() = 0; //Cada clase que herede de food tendrá su render donde la textura dependerá del tipo
};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position) : Food(position, Resources::FoodType::SlicedTomato) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};