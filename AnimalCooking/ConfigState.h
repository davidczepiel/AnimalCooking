#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDLGame.h"
#include "FSM.h"


class ConfigState :
	public State
{
public:
	ConfigState(AnimalCooking* ac);

private:
	SDLGame* game_;

	static void backButtonCallback(AnimalCooking* ac);
	static void resButtonCallback(AnimalCooking* ac);
	static void resButtonCallback2(AnimalCooking* ac);
	static void resButtonCallback3(AnimalCooking* ac);
	Entity* backButton_;
};

