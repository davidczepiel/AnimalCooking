#include "SwitcherGPad.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "GPadController.h"

void SwitcherGPad::update()
{
	col = 0;
	GPadController* gpad = GPadController::instance();
	bool inSameFrame = false;
	if (!playerIsChoosing_ && gpad->isAnyButtonJustPressed() && gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_A)) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		playerIsChoosing_ = true;
		inSameFrame = true;
	}
	if (!inSameFrame && playerIsChoosing_ && gpad->isAnyButtonJustPressed()) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		SDL_GameControllerButton buttonHitted = gpad->buttonJustPressed();
		if (gPad_keyToChange != buttonHitted) gPad_keyToChange = buttonHitted;
		playerIsChoosing_ = false;
	}
}

void SwitcherGPad::draw()
{
	if (playerIsChoosing_) col = 2;

	backGround_->renderFrame(RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY()), 0, col, 0);

	const string& cadena = string(SDL_GameControllerGetStringForButton(gPad_keyToChange));

	Vector2D s = Vector2D(name_->getWidth() * (size_.getY() - 20) / name_->getHeight(), size_.getY() - 20);

	Texture* c2 = SDLGame::instance()->getKeyShower().getTexture(cadena);
	
	name_->render(RECT(pos_.getX() + (size_.getX() / 2) - (s.getX() / 2) - (24), pos_.getY() + (size_.getY() / 2) - (s.getY() / 2), s.getX(), s.getY()));
	c2->render(RECT(pos_.getX() + (size_.getX() / 2) + (s.getX() / 2) - (24), pos_.getY() + size_.getY() / 2 - s.getY() / 2, 48, 48));

	col = 1;
}
