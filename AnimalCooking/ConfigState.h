#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "SDLGame.h"
#include "FSM.h"
#include "SliderBehaviour.h"

#include <fstream>

class ConfigState :
	public State
{
public:
	ConfigState(AnimalCooking* ac);
	~ConfigState();
	virtual void update();
	virtual void draw();
private:
	void saveToFile();
	void savePlayer(ofstream& f, Uint8 player, const config::Options& o);
	void saveVolumeSetting(ofstream& f);
	void saveBooleansSetting(ofstream& f);

	void loadFromFile();
	void loadPlayer(ifstream& f, Uint8 player, config::Options& o);
	void loadVolumeSetting(ifstream& f);
	void loadBooleansSetting(ifstream& f);

	void initButtons();
	void initSliders();
	void initKeyModifiers();

	static void backButtonCallback(AnimalCooking* ac);
	static void helperButtonCallback(AnimalCooking* ac);
	static void resButtonCallback(AnimalCooking* ac);

	Texture* textSliderMusic, * textSliderSound;
	Entity* salir, * helper, * res, * sliderTop, * sliderBot, * changeP1, * changeP2;


	SDLGame* game_;
	double musicLastValue_, soundLastValue;
	SliderBehaviour* sliderMusic_, * sliderSound_;
};

