#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "SDLGame.h"
#include "AnimalCooking.h"

class MenuState: public State
{
	SDLGame* game_;

	Entity* playMenuButton_ = nullptr;
	Entity* optionsMenu_ = nullptr;
	Entity* creditsMenu_ = nullptr;

	Transform* playMenuTr_ = nullptr;
	Transform* optionsMenuTr_ = nullptr;
	Transform* creditsMenuTr_ = nullptr;

	//static void playMenuCallback(SDLGame* game);		
	//static void optionsMenuCallback(SDLGame* game);	
	//static void creditsMenuCallback(SDLGame* game);	
public:
	MenuState();
	~MenuState() {};
};

