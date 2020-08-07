#include "RainAdversity.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

RainAdversity::RainAdversity(MultipleAdversityManager* mam) :
	Adversity(mam), 
	lastTick_(0),
	cadence_(500),
	animationFrame_(),
	lightingStrike_(false),
	lightingStrikeDone_(false),
	lastLightingTick_(),
	lastLightingFrame_(),
	lightingFrameCadence_(100),
	explosionFrameCadence_(10)
	{
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
		rainTimer_->setTime(2000);
		lastFrame_ = 0;
		frameTime_ = 75;
		started_ = false;
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainTimer_);

		//----------Rect del rayo-----------
		rectLighting_.h = 157 * 4;
		rectLighting_.w = 40 * 4;
		rectLighting_.y = -50;
		rectLighting_.x = (SDLGame::instance()->getWindowWidth() / 3) * 2;

		lightingTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LightingStrike);
		explosionTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LightingExplosion);
}

void RainAdversity::update()
{
	rainTimer_->update();

	if (rainTimer_->isTimerEnd() && !lightingStrike_ && !lightingStrikeDone_ && !explosionDone_) {
		lastLightingTick_ = SDL_GetTicks();
		lastExplosionTick_ = SDL_GetTicks();
		lightingStrike_ = true;
	}

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
	//Si aun no ha caido el rayo
	else if (lightingStrike_) {
		if (!lightingStrikeDone_ && SDL_GetTicks() - lastLightingTick_ >= lightingFrameCadence_) {
			lastLightingTick_ = SDL_GetTicks();
			lastLightingFrame_++;
			if (lastLightingFrame_ > 7) {
				lightingStrikeDone_ = true;
			}
		}
		if (SDL_GetTicks() - lastExplosionTick_ >= explosionFrameCadence_) {
			lastExplosionTick_ = SDL_GetTicks();
			lastExplosionFrame_++;
			if (lastExplosionFrame_ > 25) {
				lightingStrike_ = false;
				explosionDone_ = true;
			}
			if (lastExplosionFrame_ == 13) {
				multipleAdversityMngr_->getFirePool()->activateFire(RECT(rectLighting_.x, rectLighting_.y + rectLighting_.h - 64, 64 * 2, 64 * 2));
				multipleAdversityMngr_->getFirePool()->activateFire(RECT(rectLighting_.x, rectLighting_.y + rectLighting_.h, 64, 64));
				multipleAdversityMngr_->getFirePool()->activateFire(RECT(rectLighting_.x + 64, rectLighting_.y + rectLighting_.h, 64, 64));
			}
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
	if (lightingStrike_) {
		if(!lightingStrikeDone_) lightingTexture_->renderFrame(rectLighting_, 0, lastLightingFrame_, 0);
		explosionTexture_->renderFrame(RECT(rectLighting_.x, rectLighting_.y + rectLighting_.h - 32, 64 * 2, 64 * 2), lastExplosionFrame_ / 8, lastExplosionFrame_ % 8, 0);
	}
}
void RainAdversity::reset() {
	//Recorro todos los utensilios y en caso de que les esté dando con la lluvia les digo que devuelvan sus timers de suciedad a la normalidad
	rainTimer_->timerReset();
}

void RainAdversity::start()
{
	rainTimer_->timerReset();
	rainTimer_->timerStart();
	lightingStrike_ = false;
	lightingStrikeDone_ = false;
	explosionDone_ = false;
	lastLightingFrame_ = 0;
}
