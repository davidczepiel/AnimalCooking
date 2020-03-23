#pragma once
#include "DishPool.h"
#include "Interactive.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Transport.h"

class DishStack : public Entity,public Interactive
{
public:

	DishStack(int maxDishes_,Transport* t1,Transport* t2,EntityManager* mng);
	 ~DishStack() { }


	Dish* addNewDish(Vector2D pos, Transport* t1, Transport* t2);
	void removeDish(Dish* d);
	virtual void action1(int id);
private:
	int maxDishes;
	DishPool* dishPool = nullptr;
};

