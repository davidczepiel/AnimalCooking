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

	Entity* resumeButton = nullptr;
	Entity* configButton = nullptr;
	Entity* menuButton = nullptr;
	Entity* closeButton = nullptr;
	Entity* padNavigation = nullptr;

	static void configCallback(AnimalCooking* ac);
	static void menuCallback(AnimalCooking* ac);
	static void resumeCallback(AnimalCooking* ac);
	static void closeCallback(AnimalCooking* ac);

	Texture* resumeText_;
	Texture* optionsText_;
	Texture* menuText_;
	Texture* closeText_;
};

