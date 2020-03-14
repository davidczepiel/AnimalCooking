#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"

class Food : public Pickable 
{
protected:
	Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2);

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
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMushroom, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {};
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
