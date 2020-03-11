#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"

class Food
{
protected:
	Food(Vector2D position, Resources::FoodType type);

	Vector2D position_;
	Vector2D dir_;
	Vector2D size_;

	Resources::FoodType type_;

	FoodPool* foodPool_;
	std::vector<Food*>::iterator iterator_;
public:
	void setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it);
	void Destroy();

	void setSize(Vector2D newSize) { dir_ = newSize; }
	inline Vector2D getSize() { return size_; }

	void setSpeed(Vector2D newDir) { dir_ = newDir; }
	inline Vector2D getSpeed() { return dir_; }

	void setPosition(Vector2D newPos) { position_ = newPos; }
	inline Vector2D getPosition() { return position_; }

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