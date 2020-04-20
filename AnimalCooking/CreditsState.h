#pragma once
#include "State.h"
#include "FSM.h"
#include "ButtonBehaviour.h"
#include "TexturesManager.h"
#include "SDLTexturesManager.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "Vector2D.h"

class CreditsState :
	public State
{
private:
	static void GoBackMenu(AnimalCooking* ac);
public:
	CreditsState(AnimalCooking* ac);

};

