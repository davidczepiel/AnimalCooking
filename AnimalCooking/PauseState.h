#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ConfigState.h"
#include "Transform.h"

class PauseState : public State	
{

public:
	PauseState();
	virtual ~PauseState();

private:

	Entity* resumeButton = nullptr;
	Entity* configButton = nullptr;
	Entity* menuButton = nullptr;

	static void configCallback();
	static void menuCallback();
	static void resumeCallback();
};

