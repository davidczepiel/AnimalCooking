#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "SDLGame.h"
#include "AnimalCooking.h"
#include "ConfigState.h"
#include "MapState.h"
#include "checkML.h"
#include "CreditsState.h"

class MenuState: public State
{
private:
	SDLGame* game_;

	Entity* playMenuButton_ = nullptr;
	Entity* optionsMenu_ = nullptr;
	Entity* creditsMenu_ = nullptr;
	Entity* exitButton_ = nullptr;

	Transform* playMenuTr_ = nullptr;
	Transform* optionsMenuTr_ = nullptr;
	Transform* creditsMenuTr_ = nullptr;
	Transform* exitButtonTr_ = nullptr;
	static void playMenuCallback(AnimalCooking* ac);
	static void optionsMenuCallback(AnimalCooking* ac);
	static void creditsMenuCallback(AnimalCooking* ac);
	static void closeGame(AnimalCooking* ac);
public:
	MenuState(AnimalCooking* ac);
	~MenuState() {}
};

