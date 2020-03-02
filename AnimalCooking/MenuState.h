#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "SDLGame.h"

class MenuState: public State
{
	SDLGame* game_;

	Entity* playMenuButton_ = nullptr;
	Entity* optionsMenu_ = nullptr;

	Transform* playMenuTr_ = nullptr;
	Transform* optionsMenuTr_ = nullptr;

	static void playMenuCallback();		//Hacer callback cuando se incluya *game en State
	static void optionsMenuCallback();	//Hacer callback cuando se incluya *game en State
public:
	MenuState();
	~MenuState();
};

