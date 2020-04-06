#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"
#include "Transport.h"
#include "Timer.h"

class Food : public Pickable 
{
protected:
	Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2);
	Food(Resources::FoodType type);

	Resources::FoodType type_;
	Texture* texture_;

	FoodPool* foodPool_;
	std::vector<Food*>::iterator iterator_;

	FoodTimer timer_;
public:
	void setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it);
	void setIt(std::vector<Food*>::iterator it) { iterator_ = it; };
	void Destroy();
	void startTimer() {
		timer_.timerStart();
	}

	Resources::FoodType getType() { return type_; }

	virtual void update(); //Este udate solo actualiza la posicion respecto a la direccion
	virtual void draw(); //Cada clase que herede de food tendr� su render donde la textura depender� del tipo

	virtual void action1(int player);
	virtual void onDrop(bool onFloor);
	virtual void onPick();
};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) { 
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta); 
	}
	SlicedTomato() : Food(Resources::FoodType::SlicedTomato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedLettuce() : Food(Resources::FoodType::SlicedLettuce) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedOnion() : Food(Resources::FoodType::SlicedOnion) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedMeat() : Food(Resources::FoodType::SlicedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	MashedMeat() : Food(Resources::FoodType::MashedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedCheese() : Food(Resources::FoodType::SlicedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	GratedCheese() : Food(Resources::FoodType::GratedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedPotato() : Food(Resources::FoodType::SlicedPotato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedSausage() : Food(Resources::FoodType::SlicedSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedCarrot() : Food(Resources::FoodType::SlicedCarrot) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CaughtSausage() : Food(Resources::FoodType::CaughtSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedMushroom() : Food(Resources::FoodType::SlicedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	MashedMushroom() : Food(Resources::FoodType::MashedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CaughtFish() : Food(Resources::FoodType::CaughtFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedChicken() : Food(Resources::FoodType::SlicedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CaughtClam() : Food(Resources::FoodType::CaughtClam) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Rice : public Food
{
public:
	Rice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Rice() : Food(Resources::FoodType::Rice) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Bread : public Food
{
public:
	Bread(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Bread, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Bread() : Food(Resources::FoodType::Bread) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Salad : public Food
{
public:
	Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Salad() : Food(Resources::FoodType::Salad) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Burger() : Food(Resources::FoodType::Burger) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Pizza : public Food
{
public:
	Pizza(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Pizza, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Pizza() : Food(Resources::FoodType::Pizza) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Roast : public Food
{
public:
	Roast(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Roast() : Food(Resources::FoodType::Roast) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class RiceDish : public Food
{
public:
	RiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceDish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	RiceDish() : Food(Resources::FoodType::RiceDish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class HotDog : public Food
{
public:
	HotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::HotDog, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	HotDog() : Food(Resources::FoodType::HotDog) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Risotto : public Food
{
public:
	Risotto(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Risotto, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Risotto() : Food(Resources::FoodType::Risotto) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class CookedFish : public Food
{
public:
	CookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CookedFish() : Food(Resources::FoodType::CookedFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class FriedVegs : public Food
{
public:
	FriedVegs(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	FriedVegs() : Food(Resources::FoodType::FriedVegs) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class BakedChicken : public Food
{
public:
	BakedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	BakedChicken() : Food(Resources::FoodType::BakedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class FrenchFries : public Food
{
public:
	FrenchFries(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FrenchFries, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	FrenchFries() : Food(Resources::FoodType::FrenchFries) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class CookedClams : public Food
{
public:
	CookedClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedClams, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CookedClams() : Food(Resources::FoodType::CookedClams) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class RiceAndClams : public Food
{
public:
	RiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceAndClams, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	RiceAndClams() : Food(Resources::FoodType::RiceAndClams) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class MashedMeatSkillet : public Food
{
public:
	MashedMeatSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeatSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	MashedMeatSkillet() : Food(Resources::FoodType::MashedMeatSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class CaughtSausageSkillet : public Food
{
public:
	CaughtSausageSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausageSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	CaughtSausageSkillet() : Food(Resources::FoodType::CaughtSausageSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class SlicedPotatoSkillet : public Food
{
public:
	SlicedPotatoSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotatoSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	SlicedPotatoSkillet() : Food(Resources::FoodType::SlicedPotatoSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Poop : public Food
{
public:
	Poop(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Empty, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Poop() : Food(Resources::FoodType::Empty) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class PizzaMass : public Food
{
public:
	PizzaMass(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::PizzaMass, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	PizzaMass() : Food(Resources::FoodType::PizzaMass) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};

class Dress : public Food
{
public:
	Dress(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Dress, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
	Dress() : Food(Resources::FoodType::Dress) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::ComidaMuerta);
	}
};


