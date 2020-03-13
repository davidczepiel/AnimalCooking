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
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position) : Food(position, Resources::FoodType::SlicedLettuce) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position) : Food(position, Resources::FoodType::SlicedOnion) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position) : Food(position, Resources::FoodType::SlicedMeat) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position) : Food(position, Resources::FoodType::MashedMeat) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position) : Food(position, Resources::FoodType::SlicedCheese) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position) : Food(position, Resources::FoodType::GratedCheese) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position) : Food(position, Resources::FoodType::SlicedPotato) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position) : Food(position, Resources::FoodType::SlicedSausage) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position) : Food(position, Resources::FoodType::SlicedCarrot) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position) : Food(position, Resources::FoodType::CaughtSausage) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position) : Food(position, Resources::FoodType::SlicedMushroom) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position) : Food(position, Resources::FoodType::MashedMushroom) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position) : Food(position, Resources::FoodType::CaughtFish) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position) : Food(position, Resources::FoodType::SlicedChicken) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position) : Food(position, Resources::FoodType::CaughtClam) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
