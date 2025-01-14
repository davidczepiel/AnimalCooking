#include "PlayState.h"
#include "FSM.h"
#include "PauseState.h"
#include "EndState.h"
#include "Timer.h"

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
		if (dynamic_cast<AdversityTimer*>(t) != nullptr) continue;

		t->timerReset();
		if(dynamic_cast<CookerTimer*>(t) == nullptr)
			t->timerStart();
	}
}

void PlayState::goToEndState(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->haltMusic();
	SDLGame::instance()->getAudioMngr()->haltChannel(-1);
	SDLGame::instance()->getFSM()->pushState(new EndState(ac));
}



