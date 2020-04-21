#pragma once
#include "State.h"
class MapState :public State
{
private:
	SDLGame* game_;
public:
	MapState(AnimalCooking* ac);
	static void screenLoaderCallback(AnimalCooking* ac);
	static void backButtonCallback(AnimalCooking* ac);
};