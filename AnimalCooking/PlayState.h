#pragma once

#include "State.h"

class PlayState : public State
{
public:
	PlayState() : State() { game_ = SDLGame::instance(); }
	~PlayState() {}
	virtual void handleEvent();
private:
	SDLGame* game_ = nullptr;
};

