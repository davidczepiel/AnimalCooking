#pragma once

#include "State.h"
#include "EndState.h"
#include "PauseState.h"
#include "Manager.h"
class PlayState : public State
{
public:
	PlayState() : State() {
		Entity* morir = stage->addEntity();
		morir->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2, 50),Vector2D(),300,100,0);
		morir->addComponent<ButtonBehaviour>(goToEndState);
		morir->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button),nullptr);
		Entity* pausar = stage->addEntity();
		pausar->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2, 150), Vector2D(), 300, 100, 0);
		pausar->addComponent<ButtonBehaviour>(goToPauseState);
		pausar->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	}
	void update() override { 
		State::update(); 
		cout << "Me gustan las patatas" << endl; };
	//void draw() override {};

	//virtual void handleEvent();
private:
	static void goToEndState();
	static void goToPauseState();
};

