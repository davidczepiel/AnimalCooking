#include "IntroState.h"
#include "FSM.h"
#include "MenuState.h"

void IntroState::update()
{
	State::update();
	if (!firstBeep_) {
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::OrderRecieved, 0, 1);
		firstBeep_ = true;
	}

	if (animPart_ == AnimPart::arriving) {
		logoRect_.x += logoSpeedArriving_;

		if (logoRect_.x >= SDLGame::instance()->getWindowWidth() / 2) animPart_ = AnimPart::middle;
	}
	else if (animPart_ == AnimPart::middle) {
		logoRect_.x -= logoSpeedMiddle_;

		if (logoRect_.x <= (SDLGame::instance()->getWindowWidth() / 2) - (logoRect_.w * 0.75) ) {
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::IngredientSpawned, 0, 2);
			animPart_ = AnimPart::leaving;
		}
	}
	else if (animPart_ == AnimPart::leaving) {
		logoRect_.x += logoSpeedLeaving_;

		if (logoRect_.x >= SDLGame::instance()->getWindowWidth()) SDLGame::instance()->getFSM()->changeState(new MenuState(app));
	}
}

void IntroState::draw()
{
	logoTexture_->render(logoRect_);
}
