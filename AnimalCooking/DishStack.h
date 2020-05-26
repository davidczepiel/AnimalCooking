#pragma once
#include "DishPool.h"
#include "Interactive.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Transport.h"
#include "FoodPool.h"

class DishStack : public Entity, public Interactive
{
public:
	DishStack(Vector2D pos, int maxDishes_, Transport* t1, Transport* t2, EntityManager* mng, DishPool* dp, FoodPool* fp);
	~DishStack() { }

	void setDishSize(const Vector2D& size) { dishSize_ = size; }
	Dish* addNewDish(Vector2D pos);
	void removeDish(Dish* d);
	virtual void action1(int id);
	virtual void feedback(int id);
private:
	DishPool* dishPool = nullptr;
	FoodPool* foodPool = nullptr;
	Vector2D dishSize_;

	int maxDishes;
};

