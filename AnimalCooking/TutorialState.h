#pragma once
#include "State.h"
#include "TutorialManager.h"

class TutorialState : public State
{
public:
	TutorialState(AnimalCooking* ac);
	virtual void update();
	virtual void draw();
	TutorialManager* getTutorialManager() const { return tutorialManager; }
private:
	static void GoBackMenu(AnimalCooking* ac);
	static void moveLeft(AnimalCooking* ac);
	static void moveRight(AnimalCooking* ac);

	static void goTo1(AnimalCooking* ac);
	static void goTo2(AnimalCooking* ac);
	static void goTo3(AnimalCooking* ac);
	static void goTo4(AnimalCooking* ac);
	static void goTo5(AnimalCooking* ac);
	static void goTo6(AnimalCooking* ac);
	SDLGame* game_;
	TutorialManager* tutorialManager;

	Texture* backGround_;

	Entity* goLeftButton, *goRightButton;
};

