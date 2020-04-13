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
	player1YPosition = tP1->getPos().getY();
	player2YPosition = tP2->getPos().getY();
}

void HookAdversity::Start() {
	player1YPosition = tP1->getPos().getY();
	player2YPosition = tP2->getPos().getY();
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
		if (!catched) Catching(advancedTicks);
		else if (catched && !changedPositions) Lifting(advancedTicks);
		else if (catched && changedPositions && !droped) GoingDown(advancedTicks);
		else if (catched && changedPositions && droped) Ending(advancedTicks);
	}
}
void HookAdversity::Move(bool down, int advancedTicks) {
	if (down) {
		if (drawingAreaHook1.y + drawingAreaHook1.h < player1YPosition)
			drawingAreaHook1.y += (advancedTicks * hook1Vel);
		if (drawingAreaHook2.y + drawingAreaHook2.h < player2YPosition)
			drawingAreaHook2.y += (advancedTicks * hook2Vel);
	}
	else {
		if (drawingAreaHook1.y + drawingAreaHook1.h > 0)
			drawingAreaHook1.y -= (advancedTicks * hook1Vel);
		if (drawingAreaHook2.y + drawingAreaHook2.h > 0)
			drawingAreaHook2.y -= (advancedTicks * hook2Vel);
	}
}
void HookAdversity::SetContentPos(Transform* contentHook1, Transform* contentHook2) {
	contentHook1->setPos(Vector2D(contentHook1->getPos().getX(), drawingAreaHook1.y + drawingAreaHook1.h - contentHook1->getH()));
	contentHook2->setPos(Vector2D(contentHook2->getPos().getX(), drawingAreaHook2.y + drawingAreaHook2.h - contentHook2->getH()));
}

void HookAdversity::Catching(int advancedTicks) {
	Move(true, advancedTicks);
	if (drawingAreaHook1.y + drawingAreaHook1.h >= player1YPosition && drawingAreaHook2.y + drawingAreaHook2.h >= player2YPosition) {
		if (SDL_GetTicks() - lastFrame > frameTime) {
			lastFrame = SDL_GetTicks();
			animationFrame++;
			if (animationFrame < 5)
				clipArea.x = animationFrame * clipArea.w;
			else {
				animationFrame = 4;
				catched = true;
			}
		}
	}
}
void HookAdversity::Lifting(int advancedTicks) {
	Move(false, advancedTicks);
	SetContentPos(tP1, tP2);
	if (drawingAreaHook1.y + drawingAreaHook1.h <= 0 && drawingAreaHook2.y + drawingAreaHook2.h <= 0) {
		Vector2D positionP1 = tP1->getPos();
		Vector2D positionP2 = tP2->getPos();
		tP1->setPos(positionP2);
		tP2->setPos(positionP1);
		changedPositions = true;
	}
}

void HookAdversity::GoingDown(int advancedTicks) {
	Move(true, advancedTicks);
	SetContentPos(tP2, tP1);
	if (drawingAreaHook1.y + drawingAreaHook1.h >= player1YPosition && drawingAreaHook2.y + drawingAreaHook2.h >= player2YPosition) {
		if (SDL_GetTicks() - lastFrame > frameTime) {
			lastFrame = SDL_GetTicks();
			animationFrame--;
			if (animationFrame >= 0)
				clipArea.x = animationFrame * clipArea.w;
			else {
				animationFrame = 0;
				droped = true;
			}
		}
	}
}

void HookAdversity::Ending(int advancedTicks) {
	Move(false, advancedTicks);
	if (drawingAreaHook1.y + drawingAreaHook1.h <= 0 && drawingAreaHook2.y + drawingAreaHook2.h <= 0) {
		//Devolver a los players a un estado normal
	}
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
