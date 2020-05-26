#pragma once
#include "State.h"
#include "FSM.h"
#include "ButtonBehaviour.h"
#include "TexturesManager.h"
#include "SDLTexturesManager.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "Vector2D.h"
#include "GPadController.h"

class CreditsState :
	public State
{
public:
	CreditsState(AnimalCooking* ac);
	virtual void draw();
	virtual void update();
private:
	static void GoBackMenu(AnimalCooking* ac);
	SDLGame* game_;
};

