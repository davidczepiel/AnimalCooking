#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "SDLGame.h"
#include "AnimalCooking.h"
#include "ConfigState.h"
#include "MapState.h"
#include "CreditsState.h"

class MenuState: public State
{
private:
	SDLGame* game_;

	Entity* playMenuButton_ = nullptr;
	Entity* optionsMenu_ = nullptr;
	Entity* creditsMenu_ = nullptr;

	Transform* playMenuTr_ = nullptr;
	Transform* optionsMenuTr_ = nullptr;
	Transform* creditsMenuTr_ = nullptr;
	static void playMenuCallback();		
	static void optionsMenuCallback();	
	static void creditsMenuCallback();	
public:
	MenuState();
	~MenuState() {}
};

