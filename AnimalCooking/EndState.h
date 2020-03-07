#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "Transform.h"
#include "Vector2D.h"
class EndState :
	public State
{
private:
	//Cuando se cambie el callback por std::function se quita el static (y quizá el sdlGame)
	static void goToMapState();
	static void goToLoadState();
	static void goToMenuState();
public:
	EndState();

};

