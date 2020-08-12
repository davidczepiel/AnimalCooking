#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ConfigState.h"
#include "Transform.h"
#include "ButtonPadNavigation.h"

class PauseState : public State	
{
public:
	PauseState(AnimalCooking* ac);
	virtual ~PauseState();
	virtual void draw();
	virtual void update();

private:
	static void restartCallback(AnimalCooking* ac);
	static void optionsCallback(AnimalCooking* ac);
	static void resumeCallback(AnimalCooking* ac);
	static void closeCallback(AnimalCooking* ac);

	Entity* resumeButton = nullptr;
	Entity* restartButton = nullptr;
	Entity* optionsButton = nullptr;
	Entity* closeButton = nullptr;
	Entity* padNavigation = nullptr;
	Texture* resumeText_;
	Texture* restartText_;
	Texture* optionsText_;
	Texture* closeText_;
};

