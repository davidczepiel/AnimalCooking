#pragma once

#include "State.h"
#include "EndState.h"
#include "PauseState.h"
#include "Manager.h"
class PlayState : public State
{
public:
	PlayState() : State() {}

	//virtual void handleEvent();
private:
	static void goToEndState();
	static void goToPauseState();
};

