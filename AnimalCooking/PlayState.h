#pragma once

#include "State.h"

#include "provisional1.h"
#include "Provisional2.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Manager.h"
class PlayState : public State
{
public:
	PlayState() : State() {
		Entity* inout = stage->addEntity();

	}
	void update() override
	{
		InputHandler* ih = SDLGame::instance()->getInputHandler();
		/*if (ih->isKeyDown(SDLK_UP))
		{
			f->previousFood();
		}
		else if (ih->isKeyDown(SDLK_DOWN))
			f->nextFood();
		else if (ih->isKeyDown(SDLK_a))
			f->addFood(new provisional1());
		else if (ih->isKeyDown(SDLK_s))
			f->addFood(new Provisional2());
		else if (ih->isKeyDown(SDLK_d))
			f->takeFood();
	}*/
    }
	
	void draw() override {};

	//virtual void handleEvent();
private:
	
};

