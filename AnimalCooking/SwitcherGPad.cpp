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
		startedTime_ = SDLGame::instance()->getTime();
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
	if (playerIsChoosing_) { 
		col = 2; 
		alpha_ = int(255 * (cos((SDLGame::instance()->getTime() - startedTime_) / 200.0) + 1) / 2.0);
	}
	else
		alpha_ = 255;

	backGround_->setAlpha(alpha_);

	backGround_->renderFrame(RECT(pos_.getX() - 145, pos_.getY() - 80, 550, 172), 0, col, 0);
	name_->render(RECT(pos_.getX() + 80, pos_.getY() + 20, name_->getWidth(), name_->getHeight()));

	Texture* c2 = SDLGame::instance()->getKeyShower().getTexture(string(SDL_GameControllerGetStringForButton(gPad_keyToChange)));

	c2->render(RECT(pos_.getX() + size_.getX() - 70 - 50, pos_.getY() + 20, 70, 70)); //70 Es el size del boton del mando

	col = 1;
}
