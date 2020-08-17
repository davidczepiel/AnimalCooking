#include "SwitcherKeyboard.h"
#include "InputHandler.h"
#include "KeyBoardController.h"
#include "SDLGame.h"

void SwitcherKeyboard::update()
{
	InputHandler* ih = InputHandler::instance();
	SDL_Point mousePosition = { ih->getMousePos().getX(), ih->getMousePos().getY() };
	SDL_Rect rect = RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY());

	bool aux = (SDL_PointInRect(&mousePosition, &rect));
	if (aux) col = 0;
	else col = 1;

	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
		playerIsChoosing_ = aux;
		if (playerIsChoosing_) {
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		}
	}

	if (playerIsChoosing_ && ih->keyDownEvent()) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		SDL_Keycode keyHitted = ih->getLastKeyPressed();
		if (keyToChange_ != keyHitted) keyToChange_ = keyHitted;
		playerIsChoosing_ = false;
	}
}

void SwitcherKeyboard::draw()
{
	size_t aux = col;
	if (playerIsChoosing_) aux = 2;

	backGround_->renderFrame(RECT(pos_.getX() - 145, pos_.getY() - 80, 550, 172), 0, aux, 0);

	const string& cadena = string(SDL_GetKeyName(keyToChange_));

	Texture c2 = Texture(SDLGame::instance()->getRenderer(), cadena,
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese70), { COLOR(0xcc636dff) });
	name_->render(RECT(pos_.getX() + 80, pos_.getY() + 20, name_->getWidth(), name_->getHeight()));
	c2.render(RECT(pos_.getX() + size_.getX() - c2.getWidth() - 50, pos_.getY() + 20, c2.getWidth(), c2.getHeight()));
}
