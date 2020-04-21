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
	void leftState();
	void rightState();
	void selectedState();

	static void playMenuCallback();		
	static void optionsMenuCallback();	
	static void creditsMenuCallback();	
public:
	MenuState();
	~MenuState();
};

