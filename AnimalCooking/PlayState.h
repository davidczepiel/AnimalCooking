#pragma once

#include "State.h"
#include "Food.h"
#include "FoodMotion.h"
#include "FoodViewer.h"

#include "provisional1.h"
#include "Provisional2.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Manager.h"
#include "DishPool.h":
#include "DishStack.h"
class PlayState : public State
{
public:
	PlayState() : State() {
		Entity* dishes = stage->addEntity();
		 dp=dishes->addComponent<DishPool>();
	  ds = dishes->addComponent<DishStack>(5);
		
		
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
	 */

		/*if (ih->isKeyDown(SDLK_UP))
		{
			ds->getDish();
		}
		else if (ih->isKeyDown(SDLK_DOWN)) {
			ds->removeDish();
		}*/


    }
	
	void draw() override {};

	//virtual void handleEvent();
private:
	DishPool* dp = nullptr;
	DishStack* ds = nullptr;
	
};

