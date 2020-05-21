#pragma once
#include "State.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "Transform.h"
#include "Vector2D.h"
class EndState : public State
{
private:
	//Cuando se cambie el callback por std::function se quita el static (y quizá el sdlGame)
	static void goToMapState(AnimalCooking* ac);
	static void goToLoadState(AnimalCooking* ac);
	static void goToMenuState(AnimalCooking* ac);
	static void resetLevel(AnimalCooking* ac);

	void createButtons();
	void createPlayers();
	void draw() override;

	int score;
	int maxScore;
	Texture* background = nullptr;
	bool getNewLevel = false;
public:
	EndState(AnimalCooking* ac);

};

