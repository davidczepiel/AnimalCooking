#pragma once
#include "State.h"
class MapState :public State
{
private:
	SDLGame* game_;

	Texture* jugarText;
	Texture* volverText;
public:
	MapState(AnimalCooking* ac);
	~MapState() { delete jugarText; delete volverText; }
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);
};