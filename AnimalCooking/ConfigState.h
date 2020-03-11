#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDLGame.h"


class ConfigState :
	public State
{
	SDLGame* game_;

	Entity* backButton_;

public:
	
	ConfigState();

	static void backButtonCallback(SDLGame* game);

};

