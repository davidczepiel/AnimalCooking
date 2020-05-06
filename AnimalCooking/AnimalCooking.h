#pragma once

#include <vector>
#include "EndState.h"
#include "Manager.h"
#include "SDLGame.h"
#include "MenuState.h"
#include "FSM.h"

class AnimalCooking {

public:
	AnimalCooking();
	virtual ~AnimalCooking();

	// from SDLGame
	void start();
	void stop();


private:
	void initGame();
	void closeGame();
	void handleInput();
	void update();
	void render();
	bool pauseRequest();

	SDLGame* game_;

	bool exit_;
};
