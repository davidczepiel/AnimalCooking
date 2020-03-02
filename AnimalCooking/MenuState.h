#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "Transform.h"

class MenuState: public State
{
	Entity* playMenuButton = nullptr;
	Entity* optionsMenu = nullptr;

	Transform* playMenuTr_ = nullptr;
	Transform* optionsMenuTr_ = nullptr;

	static void playMenuCallback();		//Hacer callback cuando se incluya *game en State
	static void optionsMenuCallback();	//Hacer callback cuando se incluya *game en State
public:
	MenuState();
	~MenuState();
};

