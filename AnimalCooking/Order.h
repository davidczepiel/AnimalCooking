#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2D.h"
#include "Resources.h"
#include "SDLGame.h"

class Order
{
public:
	Order(Vector2D pos, Texture* orderText, int nIngredients, Resources::FoodType finalProduct, Uint32 maxTime)
		: position_(pos), orderTetxure_(orderText), nIngredients_(nIngredients), finalProduct_(finalProduct), anger_(), maxTime_(maxTime)
	{
		startTime_ = SDLGame::instance()->getTime();
	}

	void setPos(Vector2D pos) { position_ = pos; }
	Vector2D getPos() { return position_; }

	Texture* getOrderText() { return orderTetxure_; }

	Uint32 getStartTime() { return startTime_; }
	Uint32 getMaxTime() { return maxTime_; }
	int getNumIngs() { return nIngredients_; }

	Resources::FoodType getFinalProduct() { return finalProduct_; }

	//El anger debe ser entre 0 y 1
	void setAnger(double Anger) { anger_ = Anger; }
	double getAnger() const { return anger_; }

private:
	Vector2D position_;
	Texture* orderTetxure_;
	Uint32 startTime_, maxTime_;
	int nIngredients_;
	Resources::FoodType finalProduct_;
	double anger_;

};