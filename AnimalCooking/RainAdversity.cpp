#include "RainAdversity.h"
#include "AdversityManager.h"
#include "MultipleAdversityManager.h"

RainAdversity::RainAdversity(AdversityManager* am, MultipleAdversityManager* mam) :Adversity(am, mam)
{
	rainTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo);
	if (adversityMngr_ != nullptr)
		utensilsPool = &adversityMngr_->getUtensilsPool()->getPool();
	else
		utensilsPool = &multipleAdversityMngr_->getUtensilsPool()->getPool();

	drawingArea.x = SDLGame::instance()->getWindowWidth() / 2;
	drawingArea.y = 0;
	drawingArea.w = drawingArea.x;
	drawingArea.h = SDLGame::instance()->getWindowHeight();
	clipArea.x = 0;
	clipArea.y = 0;
	clipArea.w = 128;
	clipArea.h = 128;
	dirtSpeedUp = -4000;
	rainTimer.setTime(5000);
	lastFrame = 0;
	frameTime = 50;
	started = false;
}

void RainAdversity::update()
{
	//Si no ha comenzado la adversidad comenzamos
	if (!rainTimer.isStarted()) rainTimer.timerStart();
	rainTimer.update();
	//Si el timer no ha acabado hago que se ensucien más rapido los utensilios que estén siendo dados por la lluvia
	if (!rainTimer.isTimerEnd()) {
		for (int i = 0; i < utensilsPool->size(); i++) {
			if (Collisions::collides(Vector2D(drawingArea.x, drawingArea.y), drawingArea.w, drawingArea.h,
				utensilsPool->at(i)->getPos(), utensilsPool->at(i)->getSize().getX(), utensilsPool->at(i)->getSize().getY()))
				utensilsPool->at(i)->changeDirtySpeed(dirtSpeedUp);
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
	//if (SDL_GetTicks() - lastFrame >= frameTime) {
	//	lastFrame = SDL_GetTicks();
	//	animationFrame++;
	//	if (animationFrame > 3)
	//		animationFrame = 0;
	//	clipArea.x = animationFrame * clipArea.w;
	//}
}

void RainAdversity::draw()
{
	rainTexture->render(drawingArea, clipArea);
}
void RainAdversity::reset() {
	//Recorro todos los utensilios y en caso de que les esté dando con la lluvia les digo que devuelvan sus timers de suciedad a la normalidad
	rainTimer.timerReset();
	for (int i = 0; i < utensilsPool->size(); i++) {
		utensilsPool->at(i)->resetDirtTimer();
	}
}
