#pragma once
#include "Entity.h"

class Order : public Entity
{
private:
	Vector2D position_;
	Texture* orderTetxure_;
	vector<Texture*> ingsTexture_;
	double time_;
	int nIngredients_;

public:
	Order(Vector2D pos, Texture* orderText, vector<Texture*> ingsText)
		: Entity(), position_(pos), orderTetxure_(orderText), ingsTexture_(ingsText), nIngredients_(ingsText.size())
	{
		time_ = SDLGame::instance()->getTime();
	}

	void setPos(Vector2D pos) { position_ = pos; }

	Vector2D getPos() { return position_; }
	Texture* getOrderText() { return orderTetxure_; }
	vector<Texture*> getIngsText() { return ingsTexture_; }
	double getTime() { return time_; }
	int getNumIngs() { return nIngredients_; }
};