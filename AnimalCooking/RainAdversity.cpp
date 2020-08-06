#include "RainAdversity.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

RainAdversity::RainAdversity(MultipleAdversityManager* mam) :
	Adversity(mam), 
	lastTick_(0),
	cadence_(500),
	animationFrame_(){
		rainTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RainAdversity);
		utensilsPool_ = &multipleAdversityMngr_->getUtensilsPool()->getPool();

		rainTimer_ = new Timer();
		drawingArea_.x = SDLGame::instance()->getCasillaX() *8;
		drawingArea_.y = 0;
		drawingArea_.w = drawingArea_.x;
		drawingArea_.h = SDLGame::instance()->getCasillaY()*7;
		clipArea_.x = 0;
		clipArea_.y = 0;
		clipArea_.w = 202;
		clipArea_.h = 149;
		dirtSpeedUp_ = -700;
		rainTimer_->setTime(10000);
		lastFrame_ = 0;
		frameTime_ = 75;
		started_ = false;
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainTimer_);
}

void RainAdversity::update()
{
	//Si no ha comenzado la adversidad comenzamos
	if (!rainTimer_->isStarted()) rainTimer_->timerStart();
	rainTimer_->update();
	//Si el timer no ha acabado hago que se ensucien más rapido los utensilios que estén siendo dados por la lluvia
	if (!rainTimer_->isTimerEnd()) {
		for (int i = 0; i < utensilsPool_->size(); i++) {
			if (Collisions::collides(Vector2D(drawingArea_.x, drawingArea_.y), drawingArea_.w, drawingArea_.h,
				utensilsPool_->at(i)->getPos(), utensilsPool_->at(i)->getSize().getX(), utensilsPool_->at(i)->getSize().getY())) {
				if (SDL_GetTicks() - lastTick_ > cadence_) {
					lastTick_ = SDL_GetTicks();
					utensilsPool_->at(i)->changeDirtySpeed(dirtSpeedUp_);
				}
			}
			else
				utensilsPool_->at(i)->resetDirtTimer();
		}

	}
	//Si no, la adversidad se acabó
	else {
		multipleAdversityMngr_->stopAdversity(ecs::AdversityID::RainAdversity);
	}
	if (SDL_GetTicks() - lastFrame_ >= frameTime_) {
		lastFrame_ = SDL_GetTicks();
		animationFrame_++;
		if (animationFrame_ > 3)
			animationFrame_ = 0;
		clipArea_.x = animationFrame_ * clipArea_.w;
	}
}

void RainAdversity::draw()
{
	rainTexture_->render(drawingArea_, clipArea_);
}
void RainAdversity::reset() {
	//Recorro todos los utensilios y en caso de que les esté dando con la lluvia les digo que devuelvan sus timers de suciedad a la normalidad
	rainTimer_->timerReset();
	/*for (int i = 0; i < utensilsPool_->size(); i++) {
		utensilsPool_->at(i)->resetDirtTimer();
	}*/
}

void RainAdversity::start()
{
	rainTimer_->timerReset();
}
