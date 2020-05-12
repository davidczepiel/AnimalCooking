#include "SwitcherGPad.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "GPadController.h"

void SwitcherGPad::update()
{
	col = 0;
	GPadController* gpad = GPadController::instance();
	if (gpad->isAnyButtonJustPressed() && gpad->playerPressed(player_, SDL_CONTROLLER_BUTTON_A)) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		cout << "player choosing" << endl;
		playerIsChoosing_ = true;
	}

	if (playerIsChoosing_ && gpad->isAnyButtonJustPressed()) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		SDL_GameControllerButton buttonHitted = gpad->buttonJustPressed();
		if (gPad_keyToChange != buttonHitted) {
			gPad_keyToChange = buttonHitted;
			playerIsChoosing_ = false;
		}
	}
}

void SwitcherGPad::draw()
{
	if (playerIsChoosing_) col = 2;

	backGround_->renderFrame(RECT(pos_.getX(), pos_.getY(), size_.getX(), size_.getY()), 0, col, 0);
	Texture c = Texture(SDLGame::instance()->getRenderer(), name_ + " : " + string(SDL_GameControllerGetStringForButton(gPad_keyToChange)),
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), { COLOR(0x000000ff) });
	Vector2D s = Vector2D(c.getWidth() * (size_.getY() - 20) / c.getHeight(), size_.getY() - 20);

	c.render(RECT(pos_.getX() + size_.getX() / 2 - s.getX() / 2, pos_.getY() + 10, s.getX(), s.getY()));

	col = 1;
}
