#include "SwitcherKeyboard.h"
#include "InputHandler.h"
#include "KeyBoardController.h"
#include "SDL_macros.h"
#include "SDLGame.h"

void SwitcherKeyboard::update()
{
	InputHandler* ih = InputHandler::instance();
	SDL_Point mousePosition = { ih->getMousePos().getX(), ih->getMousePos().getY() };
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
		playerIsChoosing_ = (SDL_PointInRect(&mousePosition, &rect));
	}

	if (playerIsChoosing_ && ih->keyDownEvent()) {
		SDL_Keycode keyHitted = ih->getLastKeyPressed();
		if (keyToChange_ != keyHitted) {
			keyToChange_ = keyHitted;
			playerIsChoosing_ = false;
		}
	}
}

void SwitcherKeyboard::draw()
{
	backGround_->render(RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY()));
	Texture c = Texture(SDLGame::instance()->getRenderer(), string(SDL_GetKeyName(keyToChange_)), 
						SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::ARIAL12), { COLOR(0x000000ff) });
	c.render(RECT(pos_.getX() + size_.getX() / 2, pos_.getY(), c.getWidth() * size_.getY() / c.getHeight() , size_.getY()));
}
