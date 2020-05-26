#include "RainAdversity.h"
#include "AdversityManager.h"
#include "MultipleAdversityManager.h"
#include "TimerViewer.h"

RainAdversity::RainAdversity(AdversityManager* am, MultipleAdversityManager* mam) :Adversity(am, mam), lastTick(0),cadence(500)
{
	rainTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::RainAdversity);
	if (adversityMngr_ != nullptr)
		utensilsPool = &adversityMngr_->getUtensilsPool()->getPool();
	else
		utensilsPool = &multipleAdversityMngr_->getUtensilsPool()->getPool();

	rainTimer = new Timer();
	drawingArea.x = SDLGame::instance()->getCasillaX() *8;
	drawingArea.y = 0;
	drawingArea.w = drawingArea.x;
	drawingArea.h = SDLGame::instance()->getCasillaY()*7;
	clipArea.x = 0;
	clipArea.y = 0;
	clipArea.w = 202;
	clipArea.h = 149;
	dirtSpeedUp = -500;
	rainTimer->setTime(10000);
	lastFrame = 0;
	frameTime = 75;
	started = false;
	GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(rainTimer);

}

void RainAdversity::update()
{
	//Si no ha comenzado la adversidad comenzamos
	if (!rainTimer->isStarted()) rainTimer->timerStart();
	rainTimer->update();
	//Si el timer no ha acabado hago que se ensucien más rapido los utensilios que estén siendo dados por la lluvia
	if (!rainTimer->isTimerEnd()) {
		for (int i = 0; i < utensilsPool->size(); i++) {
			if (Collisions::collides(Vector2D(drawingArea.x, drawingArea.y), drawingArea.w, drawingArea.h,
				utensilsPool->at(i)->getPos(), utensilsPool->at(i)->getSize().getX(), utensilsPool->at(i)->getSize().getY())) {
				if (SDL_GetTicks() - lastTick > cadence) {
					lastTick = SDL_GetTicks();
					utensilsPool->at(i)->changeDirtySpeed(dirtSpeedUp);
				}
			}
			else
				utensilsPool->at(i)->resetDirtTimer();
		}

	}
	//Si no, la adversidad se acabó
	else {
		if (adversityMngr_ != nullptr)
			adversityMngr_->stopAdversity();
		else
			multipleAdversityMngr_->stopAdversity(ecs::AdversityID::RainAdversity);
		
	}
	if (SDL_GetTicks() - lastFrame >= frameTime) {
		lastFrame = SDL_GetTicks();
		animationFrame++;
		if (animationFrame > 3)
			animationFrame = 0;
		clipArea.x = animationFrame * clipArea.w;
	}
}

void RainAdversity::draw()
{
	rainTexture->render(drawingArea, clipArea);
}
void RainAdversity::reset() {
	//Recorro todos los utensilios y en caso de que les esté dando con la lluvia les digo que devuelvan sus timers de suciedad a la normalidad
	rainTimer->timerReset();
	for (int i = 0; i < utensilsPool->size(); i++) {
		utensilsPool->at(i)->resetDirtTimer();
	}
}
