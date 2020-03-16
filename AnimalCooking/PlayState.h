#pragma once

#include "State.h"
#include "EndState.h"
#include "PauseState.h"
#include "Manager.h"
#include "PlayerController.h"
#include "PlayerMotion.h"
#include "PlayerViewer.h"
#include "Entity.h"

#include "FoodPool.h"
#include "FoodMotion.h"
#include "FoodViewer.h"
#include "Transport.h"

#include "Food.h"

class PlayState : public State
{
public:
	PlayState() : State() {
		
		Entity* player = stage->addEntity();
		player->addComponent<Transform>(Vector2D(), Vector2D(), 64, 128, 0);
		player->addComponent<PlayerMotion>();
		player->addComponent<PlayerController>();
		player->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
		
		Transport* transportP1 = player->addComponent<Transport>();

		Entity* foodMngr = stage->addEntity();
		FoodPool* fp = foodMngr->addComponent<FoodPool>();
		foodMngr->addComponent<FoodViewer>();
		foodMngr->addComponent<FoodMotion>();

		SlicedTomato* st = new SlicedTomato(Vector2D(50, 50), transportP1, nullptr);
		fp->AddFood(st);

		transportP1->pick(st);
	}


	
private:

	static void goToEndState();
	static void goToPauseState();
};

