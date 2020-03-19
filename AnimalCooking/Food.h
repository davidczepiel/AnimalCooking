#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"

class Food : public Pickable 
{
protected:
	Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2);
	Food(Resources::FoodType type);

	Resources::FoodType type_;

	FoodPool* foodPool_;
	std::vector<Food*>::iterator iterator_;
public:
	void setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it);
	void Destroy();

	Resources::FoodType getType() { return type_; }

	virtual void update(); //Este udate solo actualiza la posicion respecto a la direccion
	virtual void draw() = 0; //Cada clase que herede de food tendrá su render donde la textura dependerá del tipo

	virtual void onDrop(bool onFloor) {};
	virtual void onPick() {};
};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) {};
	SlicedTomato() : Food(Resources::FoodType::SlicedTomato) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {};
	SlicedLettuce() : Food(Resources::FoodType::SlicedLettuce) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {};
	SlicedOnion() : Food(Resources::FoodType::SlicedOnion) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {};
	SlicedMeat() : Food(Resources::FoodType::SlicedMeat) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {};
	MashedMeat() : Food(Resources::FoodType::MashedMeat) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {};
	SlicedCheese() : Food(Resources::FoodType::SlicedCheese) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {};
	GratedCheese() : Food(Resources::FoodType::GratedCheese) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {};
	SlicedPotato() : Food(Resources::FoodType::SlicedPotato) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {};
	SlicedSausage() : Food(Resources::FoodType::SlicedSausage) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {};
	SlicedCarrot() : Food(Resources::FoodType::SlicedCarrot) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {};
	CaughtSausage() : Food(Resources::FoodType::CaughtSausage) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {};
	SlicedMushroom() : Food(Resources::FoodType::SlicedMushroom) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMushroom, p1, p2) {};
	MashedMushroom() : Food(Resources::FoodType::MashedMushroom) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {};
	CaughtFish() : Food(Resources::FoodType::CaughtFish) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {};
	SlicedChicken() : Food(Resources::FoodType::SlicedChicken) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {};
	CaughtClam() : Food(Resources::FoodType::CaughtClam) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Rice : public Food
{
public:
	Rice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice, p1, p2) {};
	Rice() : Food(Resources::FoodType::Rice) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Bread : public Food
{
public:
	Bread(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Bread, p1, p2) {};
	Bread() : Food(Resources::FoodType::Bread) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Salad : public Food
{
public:
	Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2) {};
	Salad() : Food(Resources::FoodType::Salad) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2) {};
	Burger() : Food(Resources::FoodType::Burger) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Pizza : public Food
{
public:
	Pizza(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Pizza, p1, p2) {};
	Pizza() : Food(Resources::FoodType::Pizza) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Roast : public Food
{
public:
	Roast(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast, p1, p2) {};
	Roast() : Food(Resources::FoodType::Roast) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class RiceDish : public Food
{
public:
	RiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceDish, p1, p2) {};
	RiceDish() : Food(Resources::FoodType::RiceDish) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class HotDog : public Food
{
public:
	HotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::HotDog, p1, p2) {};
	HotDog() : Food(Resources::FoodType::HotDog) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class Risotto : public Food
{
public:
	Risotto(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Risotto, p1, p2) {};
	Risotto() : Food(Resources::FoodType::Risotto) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class CookedFish : public Food
{
public:
	CookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedFish, p1, p2) {};
	CookedFish() : Food(Resources::FoodType::CookedFish) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class FriedVegs : public Food
{
public:
	FriedVegs(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs, p1, p2) {};
	FriedVegs() : Food(Resources::FoodType::FriedVegs) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class BakedChicken : public Food
{
public:
	BakedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken, p1, p2) {};
	BakedChicken() : Food(Resources::FoodType::BakedChicken) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class FrenchFries : public Food
{
public:
	FrenchFries(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FrenchFries, p1, p2) {};
	FrenchFries() : Food(Resources::FoodType::FrenchFries) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class CookedClams : public Food
{
public:
	CookedClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedClams, p1, p2) {};
	CookedClams() : Food(Resources::FoodType::CookedClams) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

class RiceAndClams : public Food
{
public:
	RiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceAndClams, p1, p2) {};
	RiceAndClams() : Food(Resources::FoodType::RiceAndClams) {}
	virtual void draw() {
		SDL_Rect destRect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta)->render(destRect);
	}
};

