#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDLGame.h"
#include "FSM.h"
#include "SliderBehaviour.h"

class ConfigState :
	public State
{
public:
	ConfigState(AnimalCooking* ac);
	virtual void update();
private:
	void initButtons();
	void initSliders();
	void initKeyModifiers();

	static void backButtonCallback(AnimalCooking* ac);
	static void resButtonCallback(AnimalCooking* ac);

	Entity* salir, * res, * sliderTop, * sliderBot, *changeP1, *changeP2;


	SDLGame* game_;
	double musicLastValue_, soundLastValue;
	SliderBehaviour* sliderMusic_, *sliderSound_;
};

