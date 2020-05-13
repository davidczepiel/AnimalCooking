#include "PlayState.h"
#include "FSM.h"
#include "PauseState.h"
#include "EndState.h"
#include "Timer.h"
/*void PlayState::handleEvent()
{
	InputHandler* ih = InputHandler::instance();
	ih->update();
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_p)) {
			//game_->getFSM()->pushState(new PauseState());
		}
	}
}*/

void PlayState::pauseTimers()
{
	for (Timer* t : timerViewer_->getTimers()) {
		t->timerPause();
	}
}

void PlayState::resumeTimers()
{
	for (Timer* t : timerViewer_->getTimers()) {
		t->timerResume();
	}
}

void PlayState::resetTimers()
{
	for (Timer* t : timerViewer_->getTimers()) {
		t->timerReset();
		if(dynamic_cast<CookerTimer*>(t) == nullptr && dynamic_cast<AdversityTimer*>(t) == nullptr)
			t->timerStart();
	}
}

void PlayState::goToEndState(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->haltMusic();
	SDLGame::instance()->getAudioMngr()->haltChannel(-1);
	SDLGame::instance()->getFSM()->pushState(new EndState(ac));
}



