#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"
#include "Transport.h"
#include "Timer.h"
#include "SDLGame.h"

class Food : public Pickable
{
public:
	virtual ~Food() { timer_ = nullptr; }

	virtual void update(); //Este udate solo actualiza la posicion respecto a la direccion
	virtual void draw();
	virtual void draw(SDL_Rect r);

	virtual void action1(int player);
	virtual void feedback(int player);
	virtual void onDrop(bool onFloor);
	void onFloor();
	virtual void onPick();

	void setFoodPool(FoodPool* foodPool, std::vector<Food*>::iterator it);
	void setIt(std::vector<Food*>::iterator it) { iterator_ = it; };
	void Destroy();
	void startTimer() { timer_->timerStart(); }
	void resetTimer() { timer_->timerReset(); }

	inline void setCanDraw(bool value) { canDraw = value; }
	inline void setInHands(bool b) { inHands = b; }

	Resources::FoodType getType() { return type_; }
	inline bool getCanDraw() { return canDraw; }

protected:
	Food(Vector2D position, Resources::FoodType type, Transport* p1, Transport* p2, Texture* explosion = nullptr);
	Food(Resources::FoodType type, Texture* explosion = nullptr);

	Texture* texture_;
	Texture* explosion_;
	FoodPool* foodPool_;
	FoodTimer* timer_;

	std::vector<Food*>::iterator iterator_;

	Resources::FoodType type_;

	bool dead = false;
	bool inHands = false;
	bool canDraw;
	bool showHelp;
	int explosionFrame_;
	int lastFrameTime_;
};

class SlicedTomato : public Food
{
public:
	SlicedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedTomato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedTomatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedTomatoFeedBack);
	}
	SlicedTomato() : Food(Resources::FoodType::SlicedTomato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedTomatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedTomatoFeedBack);
	}
};

class MashedTomato : public Food
{
public:
	MashedTomato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedTomato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedTomatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedTomatoFeedBack);
	}
	MashedTomato() : Food(Resources::FoodType::MashedTomato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedTomatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedTomatoFeedBack);
	}
};

class SlicedLettuce : public Food
{
public:
	SlicedLettuce(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedLettuce, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedLettuceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedLettuceFeedBack);
	}
	SlicedLettuce() : Food(Resources::FoodType::SlicedLettuce) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedLettuceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedLettuceFeedBack);
	}
};

class SlicedOnion : public Food
{
public:
	SlicedOnion(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedOnion, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedOnionT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedOnionFeedBack);
	}
	SlicedOnion() : Food(Resources::FoodType::SlicedOnion) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedOnionT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedOnionFeedBack);
	}
};

class SlicedMeat : public Food
{
public:
	SlicedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMeatT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMeatFeedBack);
	}
	SlicedMeat() : Food(Resources::FoodType::SlicedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMeatT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMeatFeedBack);
	}
};

class MashedMeat : public Food
{
public:
	MashedMeat(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeat, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatFeedBack);
	}
	MashedMeat() : Food(Resources::FoodType::MashedMeat) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatFeedBack);
	}
};

class SlicedCheese : public Food
{
public:
	SlicedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheeseT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
	SlicedCheese() : Food(Resources::FoodType::SlicedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCheeseT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCheeseFeedBack);
	}
};

class GratedCheese : public Food
{
public:
	GratedCheese(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedCheese, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedCheeseT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedCheeseFeedBack);
	}
	GratedCheese() : Food(Resources::FoodType::GratedCheese) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedCheeseT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedCheeseFeedBack);
	}
};

class SlicedPotato : public Food
{
public:
	SlicedPotato(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotato, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoFeedBack);
	}
	SlicedPotato() : Food(Resources::FoodType::SlicedPotato) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoFeedBack);
	}
};

class SlicedSausage : public Food
{
public:
	SlicedSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSausageT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSausageFeedBack);
	}
	SlicedSausage() : Food(Resources::FoodType::SlicedSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSausageT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSausageFeedBack);
	}
};

class SlicedCarrot : public Food
{
public:
	SlicedCarrot(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedCarrot, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCarrotT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCarrotFeedBack);
	}
	SlicedCarrot() : Food(Resources::FoodType::SlicedCarrot) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedCarrotT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedCarrotFeedBack);
	}
};

class CaughtSausage : public Food
{
public:
	CaughtSausage(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausage, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageFeedBack);
	}
	CaughtSausage() : Food(Resources::FoodType::CaughtSausage) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageFeedBack);
	}
};

class SlicedMushroom : public Food
{
public:
	SlicedMushroom(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedMushroom, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMushroomT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMushroomFeedBack);
	}
	SlicedMushroom() : Food(Resources::FoodType::SlicedMushroom) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedMushroomT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedMushroomFeedBack);
	}
};

class CaughtFish : public Food
{
public:
	CaughtFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtFishFeedBack);
	}
	CaughtFish() : Food(Resources::FoodType::CaughtFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtFishFeedBack);
	}
};

class SlicedChicken : public Food
{
public:
	SlicedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedChickenFeedBack);
	}
	SlicedChicken() : Food(Resources::FoodType::SlicedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedChickenFeedBack);
	}
};

class CaughtClam : public Food
{
public:
	CaughtClam(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtClam, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtClamT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtClamFeedBack);
	}
	CaughtClam() : Food(Resources::FoodType::CaughtClam) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtClamT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtClamFeedBack);
	}
};

class Rice : public Food
{
public:
	Rice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceFeedBack);
	}
	Rice() : Food(Resources::FoodType::Rice) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceFeedBack);
	}
};

class BreadBurger : public Food
{
public:
	BreadBurger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BreadBurger, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadBurgerFeedBack);
	}
	BreadBurger() : Food(Resources::FoodType::BreadBurger) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadBurgerFeedBack);
	}
};
class BreadHotDog : public Food
{
public:
	BreadHotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BreadHotDog, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadHotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadHotDogFeedBack);
	}
	BreadHotDog() : Food(Resources::FoodType::BreadHotDog) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BreadHotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BreadHotDogFeedBack);
	}
};

class Salad : public Food
{
public:
	Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SaladT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
	}
	Salad() : Food(Resources::FoodType::Salad, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SaladT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
	}
};

class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
	}
	Burger() : Food(Resources::FoodType::Burger, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
	}
};

class Pizza : public Food
{
public:
	Pizza(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Pizza, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaFeedBack);
	}
	Pizza() : Food(Resources::FoodType::Pizza, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaFeedBack);
	}
};

class Roast : public Food
{
public:
	Roast(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RoastT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RoastFeedBack);
	}
	Roast() : Food(Resources::FoodType::Roast, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RoastT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RoastFeedBack);
	}
};

class RiceDish : public Food
{
public:
	RiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceDish, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceDishFeedBack);
	}
	RiceDish() : Food(Resources::FoodType::RiceDish, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceDishFeedBack);
	}
};

class HotDog : public Food
{
public:
	HotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::HotDog, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::HotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::HotDogFeedBack);
	}
	HotDog() : Food(Resources::FoodType::HotDog, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::HotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::HotDogFeedBack);
	}
};

class Risotto : public Food
{
public:
	Risotto(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Risotto, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RisottoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RisottoFeedBack);
	}
	Risotto() : Food(Resources::FoodType::Risotto, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RisottoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RisottoFeedBack);
	}
};

class CookedFish : public Food
{
public:
	CookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedFish, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedFishFeedBack);
	}
	CookedFish() : Food(Resources::FoodType::CookedFish, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedFishFeedBack);
	}
};

class FriedVegs : public Food
{
public:
	FriedVegs(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegsFeedBack);
	}
	FriedVegs() : Food(Resources::FoodType::FriedVegs, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegsFeedBack);
	}
};

class BakedChicken : public Food
{
public:
	BakedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChickenFeedBack);
	}
	BakedChicken() : Food(Resources::FoodType::BakedChicken, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChickenFeedBack);
	}
};

class FrenchFries : public Food
{
public:
	FrenchFries(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FrenchFries, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FrenchFriesT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FrenchFriesFeedBack);
	}
	FrenchFries() : Food(Resources::FoodType::FrenchFries, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FrenchFriesT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FrenchFriesFeedBack);
	}
};

class CookedClams : public Food
{
public:
	CookedClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedClams, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedClamsFeedBack);
	}
	CookedClams() : Food(Resources::FoodType::CookedClams, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedClamsFeedBack);
	}
};

class RiceAndClams : public Food
{
public:
	RiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceAndClams, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceAndClamsFeedBack);
	}
	RiceAndClams() : Food(Resources::FoodType::RiceAndClams, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceAndClamsFeedBack);
	}
};

class MashedMeatSkillet : public Food
{
public:
	MashedMeatSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeatSkillet, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatSkilletFeedBack);
	}
	MashedMeatSkillet() : Food(Resources::FoodType::MashedMeatSkillet, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatSkilletFeedBack);
	}
};

class CaughtSausageSkillet : public Food
{
public:
	CaughtSausageSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausageSkillet, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageSkilletFeedBack);
	}
	CaughtSausageSkillet() : Food(Resources::FoodType::CaughtSausageSkillet, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageSkilletFeedBack);
	}
};

class SlicedPotatoSkillet : public Food
{
public:
	SlicedPotatoSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotatoSkillet, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoSkilletFeedBack);
	}
	SlicedPotatoSkillet() : Food(Resources::FoodType::SlicedPotatoSkillet, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoSkilletFeedBack);
	}
};

class Poop : public Food
{
public:
	Poop(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Empty, p1, p2, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PoopT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
	Poop() : Food(Resources::FoodType::Empty, SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PoopT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
};

class PizzaMass : public Food
{
public:
	PizzaMass(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::PizzaMass, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaMassT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaMassFeedBack);
	}
	PizzaMass() : Food(Resources::FoodType::PizzaMass) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaMassT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaMassFeedBack);
	}
};

class Dress : public Food
{
public:
	Dress(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Dress, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::DressT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::DressFeedBack);
	}
	Dress() : Food(Resources::FoodType::Dress) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::DressT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::DressFeedBack);
	}
};


