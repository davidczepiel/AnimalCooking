#pragma once
#include "FoodPool.h"
class Food 
{
private:
	Food();

	Vector2D position_;
	Vector2D dir_;

	FoodPool* foodPool_;
	std::vector<Food*>::iterator iterator_;
public:
	void setFoodPool(FoodPool* foodPool);
	void Destroy();

	void setSpeed(Vector2D newDir) { dir_ = newDir; }
	inline Vector2D getSpeed() { return dir_; }

	virtual void update();
	//Cada clase que herede de food tendrá su render donde la textura dependerá del tipo
	virtual void draw() = 0;
};