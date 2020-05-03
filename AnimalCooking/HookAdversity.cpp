#include "HookAdversity.h"
#include "AdversityManager.h"


HookAdversity::HookAdversity(AdversityManager* am, MultipleAdversityManager* mam) : Adversity(am, mam)
{
	speed = 5;
	tP1 = adversityMngr_->getTransformPlayer(Resources::Player::Player1);
	tP2 = adversityMngr_->getTransformPlayer(Resources::Player::Player2);
	hookTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo);
	clipArea.x = 0;
	clipArea.y = 0;
	clipArea.w = 128;
	clipArea.h = 128;
	//clipArea.w /= 5;

	drawingAreaHook1.x = 0;
	drawingAreaHook1.y = 0;
	drawingAreaHook1.w = 128;
	drawingAreaHook1.h = 128 ;
	drawingAreaHook2.x = 0;
	drawingAreaHook2.y = 0;
	drawingAreaHook2.w = 128;
	drawingAreaHook2.h = 128 ;

	catched = false;
	changedPositions = false;
	droped = false;

	hook1Vel = tP1->getPos().getY() / 2000;
	hook2Vel = tP2->getPos().getY() / 2000;
	lastTick = 0;
	lastFrame = 0;
	frameTime = 50;
	animationFrame = 0;

}

void HookAdversity::Start() {

	drawingAreaHook1.x = tP1->getPos().getX()-(drawingAreaHook1.w/2);
	drawingAreaHook1.y = -drawingAreaHook1.h;

	drawingAreaHook2.x = tP2->getPos().getX() - (drawingAreaHook2.w / 2);
	drawingAreaHook2.y = -drawingAreaHook2.h;

	p1OriginalPos = tP1->getPos();
	p2OriginalPos = tP2->getPos();
	playerSize = Vector2D(tP1->getW(),tP1->getH());

	lastTick = SDL_GetTicks();
	//Preparar los players para que no se muevan
}

void HookAdversity::update()
{
	if (lastTick == 0)Start();
	else {
		tP1->setVel(Vector2D(0, 0));
		tP2->setVel(Vector2D(0, 0));
		int advancedTicks = SDL_GetTicks() - lastTick;
		if (!catched) GoingDown(advancedTicks);
		else if (catched && !changedPositions) GoingUp(advancedTicks);
		else if (catched && changedPositions && !droped) GoingDown(advancedTicks);
		else if (catched && changedPositions && droped) GoingUp(advancedTicks);
	}
}

void HookAdversity::Move(bool down, int advancedTicks) {
	if (down) {
		if (drawingAreaHook1.y + drawingAreaHook1.h < p1OriginalPos.getY() +playerSize.getY())
			drawingAreaHook1.y +=  (advancedTicks * hook1Vel);
		if (drawingAreaHook2.y + drawingAreaHook2.h < p2OriginalPos.getY() + playerSize.getY())
			drawingAreaHook2.y +=  (advancedTicks * hook2Vel);
	}
	else {
		if (drawingAreaHook1.y + drawingAreaHook1.h > 0)
			drawingAreaHook1.y -= (advancedTicks * hook1Vel);
		if (drawingAreaHook2.y + drawingAreaHook2.h > 0)
			drawingAreaHook2.y -=(advancedTicks * hook2Vel);
	}
}
void HookAdversity::SetContentPos(Transform* contentHook1, Transform* contentHook2) {
	contentHook1->setPos(Vector2D(contentHook1->getPos().getX(), drawingAreaHook1.y + drawingAreaHook1.h - contentHook1->getH()));
	contentHook2->setPos(Vector2D(contentHook2->getPos().getX(), drawingAreaHook2.y + drawingAreaHook2.h - contentHook2->getH()));
}


void HookAdversity::GoingUp(int advancedTicks) {
	Move(false, advancedTicks);
	if (drawingAreaHook1.y + drawingAreaHook1.h <= 0 && drawingAreaHook2.y + drawingAreaHook2.h <= 0) {
		if (!changedPositions) {
			Vector2D positionP1 = tP1->getPos();
			Vector2D positionP2 = tP2->getPos();
			tP1->setPos(positionP2);
			tP2->setPos(positionP1);
			changedPositions = true;
		}
		else
			adversityMngr_->stopAdversity();
	}
	else
		Move(false,advancedTicks);
}

void HookAdversity::GoingDown(int advancedTicks) {
	if (drawingAreaHook1.y + drawingAreaHook1.h >= p1OriginalPos.getY() +playerSize.getY() && drawingAreaHook2.y + drawingAreaHook2.h >= p2OriginalPos.getY() + playerSize.getY()) {
		/*if (SDL_GetTicks() - lastFrame > frameTime) {
			lastFrame = SDL_GetTicks();
			animationFrame--;
			if (animationFrame >= 0)
				clipArea.x = animationFrame * clipArea.w;
			else {
				animationFrame = 0;
				droped = true;
			}
		}*/
		if (!catched)
			catched = true;
		else
		droped = true;
	}
	else
		Move(true,advancedTicks);
}


void HookAdversity::draw()
{
	hookTexture->render(drawingAreaHook1, clipArea);
	hookTexture->render(drawingAreaHook2, clipArea);
}

void HookAdversity::reset()
{
	lastTick = 0;
}
