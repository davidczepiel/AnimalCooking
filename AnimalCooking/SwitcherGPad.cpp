#include "SwitcherGPad.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "GPadController.h"

void SwitcherGPad::update()
{
	InputHandler* ih = InputHandler::instance();
	if (GPadController::instance()->playerPressed(player_, SDL_CONTROLLER_BUTTON_A)) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		playerIsChoosing_ = true;
	}

	if (playerIsChoosing_ && ih->buttonDownEvent()) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		SDL_GameControllerButton buttonHitted = ih->getLastButtonPressed(player_);
		if (gPad_keyToChange != buttonHitted) {
			gPad_keyToChange = buttonHitted;
			playerIsChoosing_ = false;
		}
	}
}

void SwitcherGPad::draw()
{
	backGround_->render(RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY()));
	Texture c = Texture(SDLGame::instance()->getRenderer(), name_ + " : " + string(SDL_GameControllerGetStringForButton(gPad_keyToChange)),
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::ARIAL12), { COLOR(0x000000ff) });
	Vector2D s = Vector2D(c.getWidth() * (size_.getY() - 20) / c.getHeight(), size_.getY() - 20);

	c.render(RECT(pos_.getX() + size_.getX() / 2 - s.getX() / 2, pos_.getY() + 10, s.getX(), s.getY()));
}
