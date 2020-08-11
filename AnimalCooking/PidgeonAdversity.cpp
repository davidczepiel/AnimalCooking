#include "PidgeonAdversity.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

PidgeonAdversity::PidgeonAdversity(MultipleAdversityManager* mam) :Adversity(mam)
{
	coming_ = false;
	standing_ = false;
	leaving_ = false;
	durationTimer_ = new Timer();
	durationTimer_->setTime(3000);
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(durationTimer_);

	pidgeonStandingTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PidgeonStandingAdversity);
	pidgeonFlyingTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PidgeonFlyingAdversity);

	drawingArea_.x = 0;
	drawingArea_.y = 0;
	drawingArea_.w = SDLGame::instance()->getWindowWidth();
	drawingArea_.h = SDLGame::instance()->getWindowHeight();

	row = 0;
	column = 0;

	lastFrame = 0;
	frameDuration = 50;

	clipArea_.x = 48*column;
	clipArea_.y = 48*row;
	clipArea_.w = 48;
	clipArea_.h = 48;
}

void PidgeonAdversity::update()
{
	durationTimer_->update();

	//Si el pajaro esta llegando para posarse
		if (coming_ && !standing_ && hasReached(0.33)) {
			standing_ = true;
			column = 0;
			drawingTexture_ = pidgeonStandingTexture_;
			frameDuration = 200;
		}
		//Si el pajaro se esta posando y preparando para irse
		else if (standing_ && !leaving_ && hasReached(0.66)) {
			leaving_ = true;
			column = 2;
			drawingTexture_ = pidgeonFlyingTexture_;
			frameDuration = 50;
		}
		//si el pajaro se esta llendo
		else if (leaving_ && hasReached(0.98)) {
			if (durationTimer_->isTimerEnd()) 
				multipleAdversityMngr_->stopAdversity(ecs::AdversityID::PidgeonAdversity);
			
		}

		if (SDL_GetTicks() - lastFrame > frameDuration) {
			lastFrame = SDL_GetTicks();
			row++;
			row %= 3;
		}

}


void PidgeonAdversity::draw()
{
	clipArea_.x = row * 48;
	clipArea_.y = column * 48;
	drawingTexture_->render(drawingArea_, clipArea_);
}

void PidgeonAdversity::reset()
{
	durationTimer_->timerReset();
	drawingTexture_ = pidgeonFlyingTexture_;
	coming_ = false;
	standing_ = false;
	leaving_ = false;
	row = 0;
	column = 0;
	frameDuration = 50;
}

void PidgeonAdversity::start()
{
	drawingTexture_ = pidgeonFlyingTexture_;
	coming_ = true;
	durationTimer_->timerReset();
	durationTimer_->timerStart();
}

bool PidgeonAdversity::hasReached(double d)
{
	if (durationTimer_->getProgress() > d)return true;
	else return false;
}
