#include "IntroState.h"

void IntroState::update()
{
	if (animPart_ == AnimPart::arriving) {
		logoRect_.x += logoSpeedArriving_;

		if (logoRect_.x >= SDLGame::instance()->getWindowWidth() / 2) animPart_ = AnimPart::middle;
	}
	else if (animPart_ == AnimPart::middle) {
		logoRect_.x -= logoSpeedMiddle_;

		if (logoRect_.x <= (SDLGame::instance()->getWindowWidth() / 2) - (logoRect_.w / 2)) animPart_ = AnimPart::leaving;
	}
	else if (animPart_ == AnimPart::leaving) {
		logoRect_.x += logoSpeedLeaving_;
	}
}

void IntroState::draw()
{
	logoTexture_->render(logoRect_);
}
