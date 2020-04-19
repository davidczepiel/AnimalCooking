#pragma once
#include "State.h"
#include "Manager.h"


class PlayState : public State
{
public:

	PlayState(EntityManager* em,AnimalCooking* ac) : State(em,ac) {

	}

private:

	static void goToEndState(AnimalCooking* ac);
	static void goToPauseState(AnimalCooking* ac);
};

