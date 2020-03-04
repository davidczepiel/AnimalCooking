#pragma once
#include "State.h"

#include "ButtonBehaviour.h"
#include "TexturesManager.h"
#include "SDLTexturesManager.h"
#include "ButtonRenderer.h"
#include "Transform.h"
#include "Vector2D.h"

class CreditsState :
	public State
{

public:
	CreditsState();
	static void GoBackMenu();

};

