#pragma once
#include "State.h"
class MapState :public State
{
private:
	SDLGame* game_;
public:
	MapState();
	static void screenLoaderCallback();
	static void backButtonCallback();
};