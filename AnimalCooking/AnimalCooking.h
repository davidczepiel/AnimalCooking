#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"
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

	static void sayHello() { cout << "HelloWorld"; }

	SDLGame* game_;
	
	FSM* fsm_;
	bool exit_;
	EntityManager* em;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
