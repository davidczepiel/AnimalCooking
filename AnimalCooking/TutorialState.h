#pragma once
#include "State.h"
#include "TutorialManager.h"

class TutorialState : public State
{
public:
	TutorialState(AnimalCooking* ac);
	virtual void update();

	TutorialManager* getTutorialManager() const { return tutorialManager; }
private:
	static void GoBackMenu(AnimalCooking* ac);
	static void moveLeft(AnimalCooking* ac);
	static void moveRight(AnimalCooking* ac);
	SDLGame* game_;
	TutorialManager* tutorialManager;
};

