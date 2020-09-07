#pragma once
#include "FoodPool.h"
#include "SDL_macros.h"
#include "Pickable.h"
#include "Transport.h"
#include "Timer.h"
#include "SDLGame.h"

#define EXPLOSION SDLGame::instance()->getTextureMngr()->getTexture(Resources::Explosion)

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
//Ensaladas-------------------------------------------------------------------------------------------------------------
class Salad : public Food
	{
	public:
		Salad(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad, p1, p2, EXPLOSION) {
			texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SaladT);
			feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
		}
		Salad() : Food(Resources::FoodType::Salad, EXPLOSION) {
			texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SaladT);
			feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SaladFeedBack);
		}
	}; 
class Salad1 : public Food
{
public:
	Salad1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad1FeedBack);
	}
	Salad1() : Food(Resources::FoodType::Salad1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad1FeedBack);
	}
};
class Salad2 : public Food
{
public:
	Salad2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad2FeedBack);
	}
	Salad2() : Food(Resources::FoodType::Salad2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad2FeedBack);
	}
};
class Salad3 : public Food
{
public:
	Salad3(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad3, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad3FeedBack);
	}
	Salad3() : Food(Resources::FoodType::Salad3, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad3FeedBack);
	}
};
class Salad4 : public Food
{
public:
	Salad4(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Salad4, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad4FeedBack);
	}
	Salad4() : Food(Resources::FoodType::Salad4, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Salad4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Salad4FeedBack);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Hamburguesas------------------------------------------------------------------------------------------------
class Burger : public Food
{
public:
	Burger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
	}
	Burger() : Food(Resources::FoodType::Burger, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BurgerFeedBack);
	}
};
class Burger1 : public Food
{
public:
	Burger1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger1FeedBack);
	}
	Burger1() : Food(Resources::FoodType::Burger1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger1FeedBack);
	}
};
class Burger2 : public Food
{
public:
	Burger2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger2FeedBack);
	}
	Burger2() : Food(Resources::FoodType::Burger2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger2FeedBack);
	}
};
class Burger3 : public Food
{
public:
	Burger3(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Burger3, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger3FeedBack);
	}
	Burger3() : Food(Resources::FoodType::Burger3, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Burger3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Burger3FeedBack);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Pizza : public Food
{
public:
	Pizza(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Pizza, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaFeedBack);
	}
	Pizza() : Food(Resources::FoodType::Pizza, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PizzaT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PizzaFeedBack);
	}
};
//-----------------------------ASADOS--------------------------------------------------------------------------------------
class Roast : public Food
{
public:
	Roast(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RoastT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RoastFeedBack);
	}
	Roast() : Food(Resources::FoodType::Roast, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RoastT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RoastFeedBack);
	}
};
class Roast1 : public Food
{
public:
	Roast1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast1FeedBack);
	}
	Roast1() : Food(Resources::FoodType::Roast1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast1FeedBack);
	}
};
class Roast2 : public Food
{
public:
	Roast2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast2FeedBack);
	}
	Roast2() : Food(Resources::FoodType::Roast2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast2FeedBack);
	}
};
class Roast3 : public Food
{
public:
	Roast3(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Roast3, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast3FeedBack);
	}
	Roast3() : Food(Resources::FoodType::Roast3, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Roast3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Roast3FeedBack);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RiceDish : public Food
{
public:
	RiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceDish, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceDishFeedBack);
	}
	RiceDish() : Food(Resources::FoodType::RiceDish, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceDishFeedBack);
	}
};

class HotDog : public Food
{
public:
	HotDog(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::HotDog, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::HotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::HotDogFeedBack);
	}
	HotDog() : Food(Resources::FoodType::HotDog, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::HotDogT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::HotDogFeedBack);
	}
};

class Risotto : public Food
{
public:
	Risotto(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Risotto, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RisottoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RisottoFeedBack);
	}
	Risotto() : Food(Resources::FoodType::Risotto, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RisottoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RisottoFeedBack);
	}
};

class CookedFish : public Food
{
public:
	CookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedFish, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedFishFeedBack);
	}
	CookedFish() : Food(Resources::FoodType::CookedFish, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedFishFeedBack);
	}
};
// VERDURAS FRITAS--------------------------------------------------------------------------------------------------------
class FriedVegs : public Food
{
public:
	FriedVegs(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegsFeedBack);
	}
	FriedVegs() : Food(Resources::FoodType::FriedVegs, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegsFeedBack);
	}
};
class FriedVegs1 : public Food
{
public:
	FriedVegs1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegs1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegs1FeedBack);
	}
	FriedVegs1() : Food(Resources::FoodType::FriedVegs1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegs1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegs1FeedBack);
	}
};
class FriedVegs2 : public Food
{
public:
	FriedVegs2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FriedVegs2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegs2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegs2FeedBack);
	}
	FriedVegs2() : Food(Resources::FoodType::FriedVegs2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FriedVegs2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FriedVegs2FeedBack);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------pollo asado---------------------------------------------------------------------
class BakedChicken : public Food
{
public:
	BakedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChickenFeedBack);
	}
	BakedChicken() : Food(Resources::FoodType::BakedChicken, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChickenFeedBack);
	}
};
class BakedChicken1 : public Food
{
public:
	BakedChicken1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChicken1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChicken1FeedBack);
	}
	BakedChicken1() : Food(Resources::FoodType::BakedChicken1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChicken1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChicken1FeedBack);
	}
};
class BakedChicken2 : public Food
{
public:
	BakedChicken2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::BakedChicken2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChicken2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChicken2FeedBack);
	}
	BakedChicken2() : Food(Resources::FoodType::BakedChicken2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BakedChicken2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::BakedChicken2FeedBack);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FrenchFries : public Food
{
public:
	FrenchFries(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FrenchFries, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FrenchFriesT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FrenchFriesFeedBack);
	}
	FrenchFries() : Food(Resources::FoodType::FrenchFries, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FrenchFriesT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FrenchFriesFeedBack);
	}
};

class CookedClams : public Food
{
public:
	CookedClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CookedClams, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedClamsFeedBack);
	}
	CookedClams() : Food(Resources::FoodType::CookedClams, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CookedClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CookedClamsFeedBack);
	}
};

class RiceAndClams : public Food
{
public:
	RiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::RiceAndClams, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceAndClamsFeedBack);
	}
	RiceAndClams() : Food(Resources::FoodType::RiceAndClams, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RiceAndClamsFeedBack);
	}
};
class SlicedFish : public Food
{
public:
	SlicedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedFish, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedFishFeedBack);
	}
	SlicedFish() : Food(Resources::FoodType::SlicedFish) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedFishFeedBack);
	}
};
class FishSkillet : public Food
{
public:
	FishSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FishSkillet, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishSkilletFeedBack);
	}
	FishSkillet() : Food(Resources::FoodType::FishSkillet, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishSkilletFeedBack);
	}
};
class FishOnStick : public Food
{
public:
	FishOnStick(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FishOnStick, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishOnStickT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishOnStickFeedBack);
	}
	FishOnStick() : Food(Resources::FoodType::FishOnStick, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishOnStickT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishOnStickFeedBack);
	}
};
class FishAndChips : public Food
{
public:
	FishAndChips(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FishAndChips, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishAndChipsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishAndChipsFeedBack);
	}
	FishAndChips() : Food(Resources::FoodType::FishAndChips, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishAndChipsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishAndChipsFeedBack);
	}
};
class FishBurger : public Food
{
public:
	FishBurger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::FishBurger, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishBurgerFeedBack);
	}
	FishBurger() : Food(Resources::FoodType::FishBurger, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FishBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::FishBurgerFeedBack);
	}
};
class Rice1 : public Food
{
public:
	Rice1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Rice1FeedBack);
	}
	Rice1() : Food(Resources::FoodType::Rice1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Rice1FeedBack);
	}
};
class Rice2 : public Food
{
public:
	Rice2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Rice2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Rice2FeedBack);
	}
	Rice2() : Food(Resources::FoodType::Rice2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Rice2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Rice2FeedBack);
	}
};
class Ice : public Food
{
public:
	Ice(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Ice, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IceFeedBack);
	}
	Ice() : Food(Resources::FoodType::Ice) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IceT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IceFeedBack);
	}
};
class IcedCookedFish : public Food
{
public:
	IcedCookedFish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedCookedFish, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedCookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedCookedFishFeedBack);
	}
	IcedCookedFish() : Food(Resources::FoodType::IcedCookedFish, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedCookedFishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedCookedFishFeedBack);
	}
};
class IcedFishOnStick : public Food
{
public:
	IcedFishOnStick(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedFishOnStick, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishOnStickT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishOnStickFeedBack);
	}
	IcedFishOnStick() : Food(Resources::FoodType::IcedFishOnStick, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishOnStickT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishOnStickFeedBack);
	}
};
class IcedFishAndChips : public Food
{
public:
	IcedFishAndChips(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedFishAndChips, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishAndChipsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishAndChipsFeedBack);
	}
	IcedFishAndChips() : Food(Resources::FoodType::IcedFishAndChips, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishAndChipsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishAndChipsFeedBack);
	}
};
class IcedFishBurger : public Food
{
public:
	IcedFishBurger(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedFishBurger, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishBurgerFeedBack);
	}
	IcedFishBurger() : Food(Resources::FoodType::IcedFishBurger, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedFishBurgerT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedFishBurgerFeedBack);
	}
};
class IcedRice1 : public Food
{
public:
	IcedRice1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedRice1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRice1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRice1FeedBack);
	}
	IcedRice1() : Food(Resources::FoodType::IcedRice1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRice1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRice1FeedBack);
	}
};
class IcedRice2 : public Food
{
public:
	IcedRice2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedRice2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRice2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRice2FeedBack);
	}
	IcedRice2() : Food(Resources::FoodType::IcedRice2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRice2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRice2FeedBack);
	}
};
class IcedRiceAndClams : public Food
{
public:
	IcedRiceAndClams(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedRiceAndClams, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRiceAndClamsFeedBack);
	}
	IcedRiceAndClams() : Food(Resources::FoodType::IcedRiceAndClams, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRiceAndClamsT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRiceAndClamsFeedBack);
	}
};
class IcedRiceDish : public Food
{
public:
	IcedRiceDish(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::IcedRiceDish, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRiceDishFeedBack);
	}
	IcedRiceDish() : Food(Resources::FoodType::IcedRiceDish, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::IcedRiceDishT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::IcedRiceDishFeedBack);
	}
};
class MashedMeatSkillet : public Food
{
public:
	MashedMeatSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::MashedMeatSkillet, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatSkilletFeedBack);
	}
	MashedMeatSkillet() : Food(Resources::FoodType::MashedMeatSkillet, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::MashedMeatSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MashedMeatSkilletFeedBack);
	}
};

class CaughtSausageSkillet : public Food
{
public:
	CaughtSausageSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::CaughtSausageSkillet, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageSkilletFeedBack);
	}
	CaughtSausageSkillet() : Food(Resources::FoodType::CaughtSausageSkillet, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::CaughtSausageSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CaughtSausageSkilletFeedBack);
	}
};

class SlicedPotatoSkillet : public Food
{
public:
	SlicedPotatoSkillet(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedPotatoSkillet, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoSkilletFeedBack);
	}
	SlicedPotatoSkillet() : Food(Resources::FoodType::SlicedPotatoSkillet, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedPotatoSkilletT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedPotatoSkilletFeedBack);
	}
};

class Poop : public Food
{
public:
	Poop(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Empty, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PoopT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
	Poop() : Food(Resources::FoodType::Empty, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::PoopT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PoopFeedBack);
	}
};


//------------------------------------------------------------------------------------------------------------------------------

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

class Nori : public Food
{
public:
	Nori(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Nori, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::NoriT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::NoriFeedBack);
	}
	Nori() : Food(Resources::FoodType::Nori) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::NoriT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::NoriFeedBack);
	}
};

class SlicedSalmon : public Food
{
public:
	SlicedSalmon(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedSalmon, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSalmonT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSalmonFeedBack);
	}
	SlicedSalmon() : Food(Resources::FoodType::SlicedSalmon) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedSalmonT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedSalmonFeedBack);
	}
};

class SlicedAvocado : public Food
{
public:
	SlicedAvocado(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::SlicedAvocado, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedAvocadoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedAvocadoFeedBack);
	}
	SlicedAvocado() : Food(Resources::FoodType::SlicedAvocado) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::SlicedAvocadoT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SlicedAvocadoFeedBack);
	}
};

class GratedChicken : public Food
{
public:
	GratedChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedChicken, p1, p2) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedChickenFeedBack);
	}
	GratedChicken() : Food(Resources::FoodType::GratedChicken) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedChickenFeedBack);
	}
};

class GratedSkilletChicken : public Food
{
public:
	GratedSkilletChicken(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::GratedSkilletChicken, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedSkilletChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedChickenFeedBack);
	}
	GratedSkilletChicken() : Food(Resources::FoodType::GratedSkilletChicken, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::GratedSkilletChickenT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::GratedChickenFeedBack);
	}
};

class Sushi1 : public Food
{
public:
	Sushi1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Sushi1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi1FeedBack);
	}
	Sushi1() : Food(Resources::FoodType::Sushi1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi1FeedBack);
	}
};

class Sushi2 : public Food
{
public:
	Sushi2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Sushi2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi2FeedBack);
	}
	Sushi2() : Food(Resources::FoodType::Sushi2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi2FeedBack);
	}
};

class Sushi3 : public Food
{
public:
	Sushi3(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Sushi3, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi3FeedBack);
	}
	Sushi3() : Food(Resources::FoodType::Sushi3, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi3FeedBack);
	}
};

class Sushi4 : public Food
{
public:
	Sushi4(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Sushi4, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi4FeedBack);
	}
	Sushi4() : Food(Resources::FoodType::Sushi4, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi4FeedBack);
	}
};

class Sushi5 : public Food
{
public:
	Sushi5(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Sushi5, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi5T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi5FeedBack);
	}
	Sushi5() : Food(Resources::FoodType::Sushi5, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Sushi5T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sushi5FeedBack);
	}
};

class Onigiri : public Food
{
public:
	Onigiri(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Onigiri, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::OnigiriT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OnigiriFeedBack);
	}
	Onigiri() : Food(Resources::FoodType::Onigiri, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::OnigiriT);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OnigiriFeedBack);
	}
};

class Teriyaki1 : public Food
{
public:
	Teriyaki1(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Teriyaki1, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki1FeedBack);
	}
	Teriyaki1() : Food(Resources::FoodType::Teriyaki1, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki1FeedBack);
	}
};

class Teriyaki2 : public Food
{
public:
	Teriyaki2(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Teriyaki2, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki2FeedBack);
	}
	Teriyaki2() : Food(Resources::FoodType::Teriyaki2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki2T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki2FeedBack);
	}
};

class Teriyaki3 : public Food
{
public:
	Teriyaki3(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Teriyaki3, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki1T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki3FeedBack);
	}
	Teriyaki3() : Food(Resources::FoodType::Teriyaki3, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki3T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki3FeedBack);
	}
};

class Teriyaki4 : public Food
{
public:
	Teriyaki4(Vector2D position, Transport* p1, Transport* p2) : Food(position, Resources::FoodType::Teriyaki4, p1, p2, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki4FeedBack);
	}
	Teriyaki4() : Food(Resources::FoodType::Teriyaki4, EXPLOSION) {
		texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Teriyaki4T);
		feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Teriyaki4FeedBack);
	}
};