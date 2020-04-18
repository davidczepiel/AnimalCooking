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
	virtual void onPick();

};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) { 
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedTomato); 
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedTomatoFeedBack);
	}
	SlicedTomato() : Food(Resources::FoodType::SlicedTomato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedTomato);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedTomatoFeedBack);
	}
};
class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedLettuce);
	}
	SlicedLettuce() : Food(Resources::FoodType::SlicedLettuce) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedLettuceFeedBack);
	}
};
class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedOnion);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedOnionFeedBack);
	}
	SlicedOnion() : Food(Resources::FoodType::SlicedOnion) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedOnion);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedOnionFeedBack);
	}
};
class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMeat);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMeatFeedBack);
	}
	SlicedMeat() : Food(Resources::FoodType::SlicedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMeat);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMeatFeedBack);
	}
};
class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeat);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatFeedBack);
	}
	MashedMeat() : Food(Resources::FoodType::MashedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeat);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatFeedBack);
	}
};
class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
	SlicedCheese() : Food(Resources::FoodType::SlicedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
};
class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedCheeseFeedBack);
	}
	GratedCheese() : Food(Resources::FoodType::GratedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedCheeseFeedBack);
	}
};
class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
	SlicedPotato() : Food(Resources::FoodType::SlicedPotato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheese);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
};
class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSausage);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSausageFeedBack);
	}
	SlicedSausage() : Food(Resources::FoodType::SlicedSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSausage);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSausageFeedBack);
	}
};
class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCarrot);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCarrotFeedBack);
	}
	SlicedCarrot() : Food(Resources::FoodType::SlicedCarrot) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCarrot);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCarrotFeedBack);
	}
};
class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausage);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageFeedBack);
	}
	CaughtSausage() : Food(Resources::FoodType::CaughtSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausage);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageFeedBack);
	}
};
class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMushroom);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMushroomFeedBack);
	}
	SlicedMushroom() : Food(Resources::FoodType::SlicedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMushroom);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMushroomFeedBack);
	}
};
/*class MashedMushroom : public Food
{
public:
	MashedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
	MashedMushroom() : Food(Resources::FoodType::MashedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tomato);
	}
};*/
class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtFish);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtFishFeedBack);
	}
	CaughtFish() : Food(Resources::FoodType::CaughtFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtFish);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtFishFeedBack);
	}
};
class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedChicken);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedChickenFeedBack);
	}
	SlicedChicken() : Food(Resources::FoodType::SlicedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedChicken);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedChickenFeedBack);
	}
};
class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtClam);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtClamFeedBack);
	}
	CaughtClam() : Food(Resources::FoodType::CaughtClam) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtClam);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtClamFeedBack);
	}
};

class Rice : public Food
{
public:
	Rice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceFeedBack);
	}
	Rice() : Food(Resources::FoodType::Rice) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceFeedBack);
	}
};

class BreadBurger : public Food
{
public:
	BreadBurger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BreadBurger, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadBurger);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadBurgerFeedBack);
	}
	BreadBurger() : Food(Resources::FoodType::BreadBurger) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadBurger);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadBurgerFeedBack);
	}
};
class BreadHotDog : public Food
{
public:
	BreadHotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BreadHotDog, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadHotDog);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadHotDogFeedBack);
	}
	BreadHotDog() : Food(Resources::FoodType::BreadHotDog) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadHotDog);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadHotDogFeedBack);
	}
};

class Salad : public Food
{
public:
	Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
	}
	Salad() : Food(Resources::FoodType::Salad) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
	}
};

class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
	}
	Burger() : Food(Resources::FoodType::Burger) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
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
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Poop);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
	Poop() : Food(Resources::FoodType::Empty) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Poop);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
};

class PizzaMass : public Food
{
public:
	PizzaMass(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::PizzaMass, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaMass);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaMassFeedBack);
	}
	PizzaMass() : Food(Resources::FoodType::PizzaMass) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaMass);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaMassFeedBack);
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


