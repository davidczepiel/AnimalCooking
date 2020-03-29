#pragma once
#include "DishPool.h"
#include "Interactive.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Transport.h"

class DishStack : public Entity,public Interactive
{
public:

	DishStack(Vector2D pos,int maxDishes_,Transport* t1,Transport* t2,EntityManager* mng,DishPool* dp);
	 ~DishStack() { }


	Dish* addNewDish(Vector2D pos);
	void removeDish(Dish* d);
	virtual void action1(int id);
private:
	int maxDishes;
	DishPool* dishPool = nullptr;
};

