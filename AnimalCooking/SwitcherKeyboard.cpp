#include "SwitcherKeyboard.h"
#include "InputHandler.h"
#include "KeyBoardController.h"
#include "SDL_macros.h"

void SwitcherKeyboard::update()
{
	InputHandler* ih = InputHandler::instance();
	KeyBoardController* kc = KeyBoardController::instance();
	SDL_Point mousePosition = { ih->getMousePos().getX(), ih->getMousePos().getY() };
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && SDL_PointInRect(&mousePosition, &rect))
		playerIsChoosing_ = true;

	if (kc->keyDownEvent()) {
		SDL_Keycode keyHitted = kc->getLastKeyPressed();
		if (keyToChange_ != keyHitted) {
			keyToChange_ = keyHitted;
			playerIsChoosing_ = false;
		}
	}
}
