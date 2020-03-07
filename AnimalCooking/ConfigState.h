#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDLGame.h"
#include "FSM.h"


class ConfigState :
	public State
{
	SDLGame* game_;

	static void backButtonCallback( );
	Entity* backButton_;

public:
	
	ConfigState();


};

