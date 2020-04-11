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

void PlayState::goToEndState() {
	SDLGame::instance()->getFSM()->pushState(new EndState());
}
void PlayState::goToPauseState() {
	SDLGame::instance()->getFSM()->pushState(new PauseState());

}


