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
		//timer_.timerStart();
	}
	void resetTimer() {
		timer_.timerReset();
	}

	Resources::FoodType getType() { return type_; }

	virtual void update(); //Este udate solo actualiza la posicion respecto a la direccion
	virtual void draw(); //Cada clase que herede de food tendr� su render donde la textura depender� del tipo
	virtual void draw(SDL_Rect r);

	virtual void action1(int player);
	virtual void feedback();
	virtual void onDrop(bool onFloor);
	void onFloor();
	virtual void onPick();

};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) { 
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato); 
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TomatoFeedBack);
	}
	SlicedTomato() : Food(Resources::FoodType::SlicedTomato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TomatoFeedBack);
	}
};
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedLettuce() : Food(Resources::FoodType::SlicedLettuce) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Onion);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OnionFeedBack);
	}
	SlicedOnion() : Food(Resources::FoodType::SlicedOnion) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Onion);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OnionFeedBack);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedMeat() : Food(Resources::FoodType::SlicedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	MashedMeat() : Food(Resources::FoodType::MashedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedCheese() : Food(Resources::FoodType::SlicedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	GratedCheese() : Food(Resources::FoodType::GratedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedPotato() : Food(Resources::FoodType::SlicedPotato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedSausage() : Food(Resources::FoodType::SlicedSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedCarrot() : Food(Resources::FoodType::SlicedCarrot) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CaughtSausage() : Food(Resources::FoodType::CaughtSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedMushroom() : Food(Resources::FoodType::SlicedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	MashedMushroom() : Food(Resources::FoodType::MashedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CaughtFish() : Food(Resources::FoodType::CaughtFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedChicken() : Food(Resources::FoodType::SlicedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CaughtClam() : Food(Resources::FoodType::CaughtClam) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Rice : public Food
{
public:
	Rice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Rice() : Food(Resources::FoodType::Rice) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Bread : public Food
{
public:
	Bread(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Bread, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Bread() : Food(Resources::FoodType::Bread) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Salad : public Food
{
public:
	Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Salad() : Food(Resources::FoodType::Salad) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Burger() : Food(Resources::FoodType::Burger) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Pizza : public Food
{
public:
	Pizza(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Pizza, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Pizza() : Food(Resources::FoodType::Pizza) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Roast : public Food
{
public:
	Roast(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Roast() : Food(Resources::FoodType::Roast) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class RiceDish : public Food
{
public:
	RiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceDish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	RiceDish() : Food(Resources::FoodType::RiceDish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class HotDog : public Food
{
public:
	HotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::HotDog, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	HotDog() : Food(Resources::FoodType::HotDog) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Risotto : public Food
{
public:
	Risotto(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Risotto, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Risotto() : Food(Resources::FoodType::Risotto) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class CookedFish : public Food
{
public:
	CookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CookedFish() : Food(Resources::FoodType::CookedFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class FriedVegs : public Food
{
public:
	FriedVegs(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	FriedVegs() : Food(Resources::FoodType::FriedVegs) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class BakedChicken : public Food
{
public:
	BakedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	BakedChicken() : Food(Resources::FoodType::BakedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class FrenchFries : public Food
{
public:
	FrenchFries(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FrenchFries, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	FrenchFries() : Food(Resources::FoodType::FrenchFries) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class CookedClams : public Food
{
public:
	CookedClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedClams, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CookedClams() : Food(Resources::FoodType::CookedClams) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class RiceAndClams : public Food
{
public:
	RiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceAndClams, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	RiceAndClams() : Food(Resources::FoodType::RiceAndClams) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class MashedMeatSkillet : public Food
{
public:
	MashedMeatSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeatSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	MashedMeatSkillet() : Food(Resources::FoodType::MashedMeatSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class CaughtSausageSkillet : public Food
{
public:
	CaughtSausageSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausageSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	CaughtSausageSkillet() : Food(Resources::FoodType::CaughtSausageSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class SlicedPotatoSkillet : public Food
{
public:
	SlicedPotatoSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotatoSkillet, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	SlicedPotatoSkillet() : Food(Resources::FoodType::SlicedPotatoSkillet) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Poop : public Food
{
public:
	Poop(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Empty, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Poop() : Food(Resources::FoodType::Empty) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class PizzaMass : public Food
{
public:
	PizzaMass(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::PizzaMass, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	PizzaMass() : Food(Resources::FoodType::PizzaMass) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};

class Dress : public Food
{
public:
	Dress(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Dress, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	Dress() : Food(Resources::FoodType::Dress) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};


