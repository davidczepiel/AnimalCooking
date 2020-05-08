#include "PlayerController.h"
#include "GameConfig.h"

void PlayerController::init()
{
	tr_ = GETCMP1_(Transform);
	ir_ = GETCMP1_(InteractionRect);
	selector_ = GETCMP1_(Selector);
	attack_ = GETCMP1_(Attack);
	animator = GETCMP1_(Animator);
	animator->setCurrentState(Animator::States::Idle);

	updateKeys(id_);
}


void PlayerController::updateKeys(int id_)
{
	if (id_ == 0) {
		config::Options::Player1 k;
		keys = {
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_UP,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_DOWN,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_LEFT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_RIGHT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_PICKUP,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_ATTACK,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_OPEN,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_PREVIOUS,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_NEXT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER1_KEYCODE_FINISHER
		};
	} else {
		config::Options::Player2 k;
		keys = {
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_UP,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_DOWN,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_LEFT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_RIGHT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_PICKUP,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_ATTACK,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_OPEN,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_PREVIOUS,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_NEXT,
			k.PLAYERCONTROLLER_KEYBOARD_PLAYER2_KEYCODE_FINISHER
		};
	}
	
}


void PlayerController::update()
{
	if(GPadController::instance()->playerControllerConnected(id_))	joystickUpdate();
	else keyUpdate();
}

void PlayerController::joystickUpdate()
{
	GPadController* gpad = GPadController::instance();
	//if (gpad->joysticksInitialised()) {
	double x = 0, y = 0;	//interactive
	//Axis------------------------
	double Xvalue = GPadController::instance()->getAxis(id_, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	if (Xvalue > 0 || Xvalue < 0)
	{
		x = Xvalue;
		tr_->setVelX(x);
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
		{
			i->onMoved(id_);
			i = nullptr;
		}
	}
	else {
		tr_->setVelX(0);
	}
	double Yvalue = GPadController::instance()->getAxis(id_, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	if (Yvalue > 0 || Yvalue < 0)
	{
		y = Yvalue;
		tr_->setVelY(Yvalue);
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
		{
			i->onMoved(id_);
			i = nullptr;
		}
	}
	else {
		tr_->setVelY(0);
	}
	ir_->setDir(x, y);
	//Botones-------------------------------
	if (ableToPress && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_A)) {
		ableToPress = false;
		cout << id_ + " ha pulsado A" << endl;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action1(id_);
			i = nullptr;
		}
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_B)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action4(id_);
		i = nullptr;
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_X) && selector_ != nullptr) {
		attack_->attack();
		animator->setCurrentState(Animator::States::Attack);
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_Y)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action5(id_);
		i = nullptr;
	}
	else if (!ableToPress&& padNotTouched())
		ableToPress = true;

	if (!dpadArrowsUsed && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_LEFT) && selector_ != nullptr)
	{
		dpadArrowsUsed = true;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action2(id_);
			i = nullptr;
		}
	}
	else if (!dpadArrowsUsed && GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) && selector_ != nullptr)
	{
		dpadArrowsUsed = true;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action3(id_);
			i = nullptr;
		}
	}
	else if (dpadArrowsUsed && dpadArrosNotUsed())
		dpadArrowsUsed = false;
}

bool PlayerController::padNotTouched() {
	if (!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_A) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_B) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_X) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_Y))
		return true;
	else 
		return false;
}

bool PlayerController::dpadArrosNotUsed() {
	if (!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_UP) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_DOWN) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_LEFT) &&
		!GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		return true;
	else
		return false;
}

void PlayerController::keyUpdate()
{
	InputHandler* keyboard = InputHandler::instance();

	int speed = 1;
	int x = 0, y = 0;

	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		if (keyboard->isKeyDown(keys.up)) {
			movKeys.up = true;
		}
		else if (keyboard->isKeyDown(keys.down)) {
			movKeys.down = true;
		}

		if (keyboard->isKeyDown(keys.right)) {
			movKeys.right = true;
		}
		else if (keyboard->isKeyDown(keys.left)) {
			movKeys.left = true;
		}

		//--------------------Botones

		if (keyboard->isKeyDown(keys.pickUp) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->action1(id_);
				i = nullptr;
			}
		}

		if (keyboard->isKeyDown(keys.attack))
		{
			attack_->attack();
			animator->setCurrentState(Animator::States::Attack);
		}

		if (keyboard->isKeyDown(keys.next) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action2(id_);
				i = nullptr;
			}
		}

		if (keyboard->isKeyDown(keys.back) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action3(id_);
				i = nullptr;
			}
		}

		if (keyboard->isKeyDown(keys.open) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action4(id_);
				i = nullptr;
			}
		}

		if (keyboard->isKeyDown(keys.finish) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action5(id_);
				i = nullptr;
			}
		}
	}

	if (keyboard->keyUpEvent()) {
		if (keyboard->isKeyUp(keys.up)) {
			movKeys.up = false;
		}
		if (keyboard->isKeyUp(keys.down)) {
			movKeys.down = false;
		}
		if (keyboard->isKeyUp(keys.right)) {
			movKeys.right = false;
		}
		if (keyboard->isKeyUp(keys.left)) {
			movKeys.left = false;
		}
	}

	if (movKeys.up) y = -1;
	else if (movKeys.down) y = 1;
	else y = 0;

	if (movKeys.right) x = 1;
	else if (movKeys.left) x = -1;
	else x = 0;

	tr_->setVelY(speed * y);
	tr_->setVelX(speed * x);

	Interactive* i = selector_->getSelect();
	if (i != nullptr)
	{
		i->onMoved(id_);
		i = nullptr;
	}

	ir_->setDir(x, y);
	if (tr_->getVel().getX() != 0 || tr_->getVel().getY() != 0)animator->setCurrentState(Animator::States::Walk);
	else animator->setCurrentState(Animator::States::Idle);

	
}
