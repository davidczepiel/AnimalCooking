#include "PlayerController.h"


void PlayerController::init()
{
	tr_ = GETCMP1_(Transform);
	ir_ = GETCMP1_(InteractionRect);
	selector_ = GETCMP1_(Selector);
	attack_ = GETCMP1_(Attack);

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
	keyUpdate();
	//joystickUpdate();
}

void PlayerController::joystickUpdate()
{
	GPadController* gpad = GPadController::instance();

	if (gpad->joysticksInitialised()) {
		double x = 0, y = 0;	//interactive
		//Axis------------------------
		if (gpad->xvalue(id_, 1) > 0 ||	gpad->xvalue(id_, 1) < 0)
		{
			tr_->setVelX(gpad->xvalue(id_,1));
			x = gpad->xvalue(id_, 1);
		}
		else {
			tr_->setVelX(0);
		}
		if (gpad->yvalue(id_, 1) > 0 || gpad->yvalue(id_, 1) < 0)
		{
			tr_->setVelY(gpad->yvalue(id_,1));
			y = gpad->xvalue(id_, 1);
		}
		else {
			tr_->setVelY(0);
		}
		ir_->setDir(x, y);
		//Botones-------------------------------
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_A)) {
			//
		}
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_B)) {
			//
		}
		if (gpad->getButtonState(id_, SDL_CONTROLLER_BUTTON_X) && selector_ != nullptr) {
			selector_->getSelect()->action1(id_);
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
	InputHandler* keyboard = InputHandler::instance();

	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		int x = 0, y = 0;	
		if (keyboard->isKeyDown(keys.up)) { tr_->setVelY(-1); y = -1; }
		else if (keyboard->isKeyDown(keys.down)) { tr_->setVelY(1); y = 1; }
		else tr_->setVelY(0);

		if (keyboard->isKeyDown(keys.right)) { tr_->setVelX(1);  x = 1;	}
		else if (keyboard->isKeyDown(keys.left)) { tr_->setVelX(-1); x = -1; }
		else tr_->setVelX(0);

		ir_->setDir(x, y);
		//--------------------Botones

		if (keyboard->isKeyDown(SDLK_k) && selector_!= nullptr)
		{ 
			Interactive* i = selector_->getSelect();
			if(i!= nullptr)
			i->action1(id_);
			i = nullptr;
		}
		if (keyboard->isKeyDown(SDLK_p))
		{ 
			attack_->attack(); 
		}
	}
	else {
		tr_->setVelX(0);
		tr_->setVelY(0);
	}
}
