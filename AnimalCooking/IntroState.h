#pragma once
#include "State.h"

class IntroState : public State
{
public:
	IntroState(AnimalCooking* ac_) : State(ac_), time_(SDL_GetTicks()) {
		logoTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LogoTenByTen);
		logoRect_.w = logoTexture_->getWidth();
		logoRect_.h = logoTexture_->getHeight();
		logoRect_.x = -logoRect_.w;
		logoRect_.y = (SDLGame::instance()->getWindowHeight() / 2) - (logoRect_.h / 2);

		animPart_ = AnimPart::arriving;

		logoSpeedArriving_ = 24;
		logoSpeedMiddle_ = 3;
		logoSpeedLeaving_ = 24;

		firstBeep_ = false;
	}
	~IntroState() {}
private:
	enum AnimPart { arriving, middle, leaving};

	void update() override;
	void draw() override;

	Texture* logoTexture_;
	SDL_Rect logoRect_;
	Uint32 time_;
	AnimPart animPart_;
	int logoSpeedArriving_;
	int logoSpeedMiddle_;
	int logoSpeedLeaving_;
	bool firstBeep_;
};

