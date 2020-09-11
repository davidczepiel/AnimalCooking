#include "IntroState.h"
#include "FSM.h"
#include "MenuState.h"

void IntroState::update()
{
	State::update();
	if (!firstBeep_) {
		SDLGame::instance()->getAudioMngr()->setChannelVolume(10, 1);
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::OrderRecieved, 0, 1);
		firstBeep_ = true;
	}

	if (animPart_ == AnimPart::arriving) {
		logoRect_.x += logoSpeedArriving_;

		if (fade_ <= 255) {
			fade_ += 6;
			if (fade_ > 255) fade_ = 255;
		}

		if (logoRect_.x >= SDLGame::instance()->getWindowWidth() / 2 - (logoRect_.w / 2)) {
			animPart_ = AnimPart::middle;
			fade_ = 255;
		}
	}
	else if (animPart_ == AnimPart::middle) {
		logoRect_.x -= logoSpeedMiddle_;

		if (logoRect_.x <= (SDLGame::instance()->getWindowWidth() / 2) - (logoRect_.w * 0.75) ) {
			SDLGame::instance()->getAudioMngr()->setChannelVolume(10, 2);
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::IngredientSpawned, 0, 2);
			animPart_ = AnimPart::stay;
			time_ = SDL_GetTicks();
		}
	}
	else if (animPart_ == AnimPart::stay) {
		if (SDL_GetTicks() > time_ + 250) {
			animPart_ = AnimPart::leaving;
		}
	}
	else if (animPart_ == AnimPart::leaving) {
		logoRect_.x += logoSpeedLeaving_;

		if (fade_ >= 0) {
			fade_ -= 14;
			if (fade_ < 0) fade_ = 0;
		}

		if (logoRect_.x >= SDLGame::instance()->getWindowWidth()) SDLGame::instance()->getFSM()->changeState(new MenuState(app));
	}
}

void IntroState::draw()
{
	logoTexture_->renderWithTint(logoRect_, fade_, fade_, fade_);
}
