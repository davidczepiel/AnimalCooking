#pragma once

#include "State.h"
#include "Food.h"
#include "FoodMotion.h"
#include "FoodViewer.h"

class PlayState : public State
{
public:
	PlayState() : State() {}
	void update() override { cout << "Me gustan las patatas" << endl; };
	void draw() override {};

	//virtual void handleEvent();
private:

};

