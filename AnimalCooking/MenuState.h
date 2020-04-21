#pragma once
#include "State.h"
#include "MenuButtonBehaviour.h"
#include "MenuButtonRenderer.h"
#include "Transform.h"
#include "SDLGame.h"
#include "AnimalCooking.h"
#include "ConfigState.h"
#include "MapState.h"
#include "checkML.h"
#include "CreditsState.h"
#include "Texture.h"

class MenuState: public State
{
	enum SelectionState { Options, Play, Credits};

private:
	SelectionState state;
	SDL_Rect backgroundRect;
	SDL_Rect ruedecillaRect;

	Texture* background;
	Texture* ruedecilla;

	Entity* leftButton_;
	Entity* rightButton_;

	void draw() override;
	void selectedState();

	static void playMenuCallback();		
	static void optionsMenuCallback();	
	static void creditsMenuCallback();	
public:
	MenuState();
	~MenuState();

	void leftState();
	void rightState();
};

