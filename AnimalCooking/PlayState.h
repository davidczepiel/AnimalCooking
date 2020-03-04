#pragma once

#include "State.h"

class PlayState : public State
{
public:
	PlayState() : State() {}
	void update() override { cout << "Me gustan las patatas" << endl; };
	void draw() override {};

	//virtual void handleEvent();
private:

};

