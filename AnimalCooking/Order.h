#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2D.h"
#include "Resources.h"
#include "SDLGame.h"

class Order
{
private:
	Vector2D position_;
	Texture* orderTetxure_;
	vector<Texture*> ingsTexture_;
	double time_;
	int nIngredients_;
	Resources::FoodType finalProduct_;
	double anger_;

public:
	Order(Vector2D pos, Texture* orderText, vector<Texture*> ingsText, Resources::FoodType finalProduct)
		: position_(pos), orderTetxure_(orderText), ingsTexture_(ingsText), nIngredients_(ingsText.size()), finalProduct_(finalProduct), anger_()
	{
		time_ = SDLGame::instance()->getTime();
	}

	void setPos(Vector2D pos) { position_ = pos; }

	Vector2D getPos() { return position_; }
	Texture* getOrderText() { return orderTetxure_; }
	vector<Texture*> getIngsText() { return ingsTexture_; }
	double getTime() { return time_; }
	int getNumIngs() { return nIngredients_; }

	Resources::FoodType getFinalProduct() { return finalProduct_; }

	//El anger debe ser entre 0 y 1
	void setAnger(double Anger) { anger_ = Anger; }
	double getAnger() const { return anger_; }
};