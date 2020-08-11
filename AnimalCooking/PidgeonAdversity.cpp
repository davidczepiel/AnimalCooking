#include "PidgeonAdversity.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

PidgeonAdversity::PidgeonAdversity(MultipleAdversityManager* mam) :Adversity(mam)
{
	durationTimer_ = new Timer();
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(durationTimer_);
	pidgeonTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RainAdversity);
	drawingArea_.x = 0;
	drawingArea_.y = 0;
	drawingArea_.w = SDLGame::instance()->getWindowWidth();
	drawingArea_.h = SDLGame::instance()->getWindowHeight();

	clipArea_.x = 0;
	clipArea_.y = 0;
	clipArea_.w = 202;
	clipArea_.h = 149;
}

void PidgeonAdversity::update()
{
	durationTimer_->update();
	if(durationTimer_->isTimerEnd())
	multipleAdversityMngr_->stopAdversity(ecs::AdversityID::RainAdversity);

}


void PidgeonAdversity::draw()
{
	pidgeonTexture_->render(drawingArea_, clipArea_);

	
}