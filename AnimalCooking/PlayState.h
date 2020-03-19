#pragma once

#include "State.h"
#include "EndState.h"
#include "PauseState.h"
#include "Manager.h"
#include "PlayerController.h"
#include "PlayerMotion.h"
#include "PlayerViewer.h"
#include "Entity.h"

class PlayState : public State
{
public:
	PlayState() : State() {

		Entity* player = stage->addEntity();
		player->addComponent<Transform>();
		player->addComponent<PlayerMotion>();
		player->addComponent<PlayerController>();
		player->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));

	}



private:

	static void goToEndState();
	static void goToPauseState();
};

