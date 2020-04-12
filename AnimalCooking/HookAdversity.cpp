#include "HookAdversity.h"
#include "AdversityManager.h"


HookAdversity::HookAdversity(AdversityManager* am) : Adversity(am)
{
	tP1 = adversityMngr_->getTransformPlayer(Resources::Player::Player2);
	tP2 = adversityMngr_->getTransformPlayer(Resources::Player::Player2);
	hookTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	clipArea.x = 0;
	clipArea.y = 0;
	clipArea.w = NULL;
	clipArea.h = NULL;
	clipArea.w /= 5;

	drawingAreaHook1.x = 0;
	drawingAreaHook1.y = 0;
	drawingAreaHook1.w = 128;
	drawingAreaHook1.h = 128 * 5;
	drawingAreaHook2.x = 0;
	drawingAreaHook2.y = 0;
	drawingAreaHook2.w = 128;
	drawingAreaHook2.h = 128 * 5;

	catchPlayerSpeed = 5;
	catched = false;
	changedPositions = false;
	droped = true;

	hook1Vel = tP1->getPos().getX() / 100;
	hook2Vel = tP2->getPos().getX() / 100;
	lastTick = 0;
	lastFrame = 0;
	frameTime = 50;
	animationFrame = 0;
}

void HookAdversity::update()
{
	if (lastTick == 0)lastTick = SDL_GetTicks();
	else {
		tP1->setVel(Vector2D(0, 0));
		tP2->setVel(Vector2D(0, 0));
		int advancedTicks = SDL_GetTicks() - lastTick;
		if (!catched) Catching(advancedTicks);
		else if (catched && !changedPositions) Lifting(advancedTicks);
		else if (catched && changedPositions) {}
		else if (catched && changedPositions && droped) {

		}

	}
}

void HookAdversity::Catching(int advancedTicks) {
	if (drawingAreaHook1.y < tP1->getPos().getY())
		drawingAreaHook1.y += (advancedTicks * hook1Vel);
	if (drawingAreaHook2.y < tP2->getPos().getY())
		drawingAreaHook2.y += (advancedTicks * hook2Vel);
	if (drawingAreaHook1.y >= tP1->getPos().getY() && drawingAreaHook2.y < tP2->getPos().getY()) {
		if (SDL_GetTicks() - lastFrame > frameTime) {
			lastFrame = SDL_GetTicks();
			animationFrame++;
			if (animationFrame < 5)
				clipArea.x = animationFrame * clipArea.w;
			catched = true;
		}
	}
}

void HookAdversity::Lifting(int advancedTicks) {
	if (drawingAreaHook1.y > 0)
		drawingAreaHook1.y -= (advancedTicks * hook1Vel);
	if (drawingAreaHook2.y >0)
		drawingAreaHook2.y -= (advancedTicks * hook2Vel);
	if (drawingAreaHook1.y <= 0 && drawingAreaHook2.y <= 0) {
		Vector2D positionP1 = tP1->getPos();
		Vector2D positionP2 = tP2->getPos();
		double aux = tP1->getPos().getX();
		tP1->setPos(positionP2);
		tP2->setPos(positionP1);
		changedPositions = true;
	}
}

void HookAdversity::GoingDown(int advancedTicks) {

}

void HookAdversity::draw()
{
}

void HookAdversity::reset()
{
	lastTick = 0;
}
