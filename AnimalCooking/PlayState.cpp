#include "PlayState.h"
#include "FSM.h"
#include "PauseState.h"
#include "EndState.h"

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
	for (Timer* t : timers) {
		t->timerPause();
	}
}

void PlayState::resumeTimers()
{
	for (Timer* t : timers) {
		t->timerResume();
	}
}

void PlayState::goToEndState(AnimalCooking* ac) {
	SDLGame::instance()->getFSM()->pushState(new EndState(ac));
}



