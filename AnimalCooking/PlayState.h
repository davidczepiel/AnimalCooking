#pragma once

#include "State.h"
#include "IngredientsPool.h"

class PlayState : public State
{
public:
	PlayState() : State() {
		cout << "PlayState" << endl;
		Entity* e = stage->addEntity();
		e->addComponent<IngredientsPool>();
	}
	void update() override {};
	void draw() override {};

	//virtual void handleEvent();
private:

};
