#pragma once

#include "State.h"
#include "Food.h"
#include "FoodMotion.h"
#include "FoodViewer.h"

class PlayState : public State
{
public:
	PlayState() : State() {
		Entity* foodMngr = stage->addEntity();
		foodMngr->addComponent<FoodPool>();
		foodMngr->addComponent<FoodViewer>();
		foodMngr->addComponent<FoodMotion>();

		SlicedTomato* st = new SlicedTomato(Vector2D(100, 100));
		foodMngr->getComponent<FoodPool>(ecs::FoodPool)->AddFood(st);

	}
	void update() override { cout << "Me gustan las patatas" << endl; };
	void draw() override {};

	//virtual void handleEvent();
private:

};

