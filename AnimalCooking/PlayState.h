#pragma once

#include "State.h"
#include "Manager.h"

class PlayState : public State
{
public:
	PlayState(EntityManager* em) : State(em) {
	}

private:

	static void goToEndState();
	static void goToPauseState();
};

