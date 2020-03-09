#include "PlayerController.h"


void PlayerController::init()
{
	tr_ = GETCMP1_(Transform);
	if (id_ == 0) {
		keys.up = SDLK_w;
		keys.down = SDLK_s;
		keys.right = SDLK_d;
		keys.left = SDLK_a;
	}
	else {
		keys.up = SDLK_UP;
		keys.down = SDLK_DOWN;
		keys.right = SDLK_RIGHT;
		keys.left = SDLK_LEFT;
	}
}

void PlayerController::update()
{
	joystickUpdate();
}

void PlayerController::joystickUpdate()
{
	GPadController* gpad = GPadController::instance();

	if (gpad->joysticksInitialised()) {
		//Axis------------------------
		if (gpad->xvalue(id_, 1) > 0 ||
			gpad->xvalue(id_, 1) < 0)
		{
			tr_->setVelX(gpad->xvalue(id_,1));
		}
		else {
			tr_->setVelX(0);
		}
		if (gpad->yvalue(id_, 1) > 0 || gpad->yvalue(id_, 1) < 0)
		{
			tr_->setVelY(gpad->yvalue(id_,1));
		}
		else {
			tr_->setVelY(0);
		}
		//Botones-------------------------------
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_A)) {
			//
		}
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_B)) {
			//
		}
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_X)) {
			//
		}
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_Y)) {
			//
		}
	}
	else {
		keyUpdate();
	}
}

void PlayerController::keyUpdate()
{
	KeyBoardController* keyboard = KeyBoardController::instance();

	if (keyboard->keyDownEvent()) {
		if (keyboard->isKeyDown(keys.up))  tr_->setVelY(-1);
		else if (keyboard->isKeyDown(keys.down)) tr_->setVelY(1);
		else tr_->setVelY(0);

		if (keyboard->isKeyDown(keys.right)) tr_->setVelX(1);
		else if (keyboard->isKeyDown(keys.left)) tr_->setVelX(-1);
		else tr_->setVelX(0);
	}
	else {
		tr_->setVelX(0);
		tr_->setVelY(0);
	}
}
