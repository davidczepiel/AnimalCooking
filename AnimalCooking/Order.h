#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2D.h"
#include "Resources.h"
#include "SDLGame.h"
#include "Timer.h"
#include "FSM.h"
#include "PlayState.h"
#include "TimerViewer.h"

class Order
{
public:
	Order(Vector2D pos, Texture* orderText, int nIngredients, Resources::FoodType finalProduct, Uint32 maxTime)
		: position_(pos), orderTetxure_(orderText), nIngredients_(nIngredients), finalProduct_(finalProduct)
	{
		timer = new Timer();
		timer->setTime(maxTime);
		timer->timerStart();
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(timer);
	}
	~Order() {
		timer = nullptr;
	}
	void update();

	void setPos(Vector2D pos) { position_ = pos; }
	Vector2D getPos() { return position_; }

	Texture* getOrderText() { return orderTetxure_; }

	int getNumIngs() { return nIngredients_; }

	Resources::FoodType getFinalProduct() { return finalProduct_; }

	//El anger debe ser entre 0 y 1
	double getAnger() { return timer->getProgress(); }

	void removeTimer() {
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->deleteTimer(timer);
	}

private:

	Timer* timer;
	Vector2D position_;
	Texture* orderTetxure_;
	int nIngredients_;
	Resources::FoodType finalProduct_;
};