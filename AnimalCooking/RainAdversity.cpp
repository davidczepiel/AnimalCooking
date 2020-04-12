#include "RainAdversity.h"
#include "AdversityManager.h"

RainAdversity::RainAdversity(AdversityManager* am):Adversity(am)
{
	rainTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo);
	//utensilsPool = &uP;
	drawingArea.x = SDLGame::instance()->getWindowWidth() / 2;
	drawingArea.y = 0;
	drawingArea.w = SDLGame::instance()->getWindowWidth() / 2;
	drawingArea.h = SDLGame::instance()->getWindowHeight();
	clipArea.x = 0;
	clipArea.y = 0;
	clipArea.w = NULL;
	clipArea.h = NULL;
	dirtSpeedUp = -1;
	rainTimer.setTime(2);
	lastFrame = 0;
	frameTime = 50;
}

void RainAdversity::update()
{
	rainTimer.update();
	if (rainTimer.isTimerEnd()) {
		rainTimer.timerReset();
		rainTimer.timerStart();
		for (int i = 0; i < utensilsPool->size(); i++) {
			if (Collisions::collides(Vector2D(drawingArea.x, drawingArea.y), drawingArea.w, drawingArea.h,
				utensilsPool->at(i)->getPos(), utensilsPool->at(i)->getSize().getX(), utensilsPool->at(i)->getSize().getY()))
				utensilsPool->at(i)->changeDirtySpeed(-dirtSpeedUp);
			else
				utensilsPool->at(i)->resetDirtTimer();
		}
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
	//Recorro todos los utensilios y en caso de que les esté dando con la lluvia les digo que 
	for (int i = 0; i < utensilsPool->size(); i++) {
		utensilsPool->at(i)->resetDirtTimer();
	}
}
