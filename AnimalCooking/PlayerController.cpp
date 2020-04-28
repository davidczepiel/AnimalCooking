#include "PlayerController.h"


void PlayerController::init()
{
	tr_ = GETCMP1_(Transform);
	ir_ = GETCMP1_(InteractionRect);
	selector_ = GETCMP1_(Selector);
	attack_ = GETCMP1_(Attack);
	animator = GETCMP1_(Animator);
	animator->setCurrentState(Animator::States::Idle);

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
	//keyUpdate();
}

void PlayerController::joystickUpdate()
{
	GPadController* gpad = GPadController::instance();
	//if (gpad->joysticksInitialised()) {
	double x = 0, y = 0;	//interactive
	//Axis------------------------
	double Xvalue = GPadController::getAxisX(id_, 0);
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
	double Yvalue = GPadController::getAxisY(id_, 1);
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
	if (ableToPress && GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_A)) {
		ableToPress = false;
		cout << id_ + " ha pulsado A" << endl;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action1(id_);
			i = nullptr;
		}
	}
	else if (ableToPress && GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_B)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action4(id_);
		i = nullptr;
	}
	else if (ableToPress && GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_X) && selector_ != nullptr) {
		attack_->attack();
		animator->setCurrentState(Animator::States::Attack);
	}
	else if (ableToPress && GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_Y)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action5(id_);
		i = nullptr;
	}
	else if (!ableToPress&& padNotTouched())
		ableToPress = true;

	if (GPadController::playerPressed(id_,SDL_CONTROLLER_BUTTON_DPAD_DOWN) && selector_ != nullptr)
	{
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action2(id_);
			i = nullptr;
		}
	}
	else if (GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_DPAD_UP) && selector_ != nullptr)
	{
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action3(id_);
			i = nullptr;
		}
	}
}

bool PlayerController::padNotTouched() {
	if (!GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_A) &&
		!GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_B) &&
		!GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_X) &&
		!GPadController::playerPressed(id_, SDL_CONTROLLER_BUTTON_Y))
		return true;
	else 
		return false;
}

void PlayerController::keyUpdate()
{
	InputHandler* keyboard = InputHandler::instance();

	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		int x = 0, y = 0;
		if (keyboard->isKeyDown(keys.up)) {
			tr_->setVelY(-1); y = -1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.down)) {
			tr_->setVelY(1); y = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		//else tr_->setVelY(0);

		if (keyboard->isKeyDown(keys.right)) {
			tr_->setVelX(1);  x = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.left)) {
			tr_->setVelX(-1); x = -1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		//else tr_->setVelX(0);

		ir_->setDir(x, y);

		if (tr_->getVel().getX() != 0 || tr_->getVel().getY() != 0)animator->setCurrentState(Animator::States::Walk);

		//--------------------Botones

		if (keyboard->isKeyDown(SDLK_k) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->action1(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(SDLK_p))
		{
			attack_->attack();
			animator->setCurrentState(Animator::States::Attack);
		}

		if (keyboard->isKeyDown(SDLK_e) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action2(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(SDLK_q) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action3(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(SDLK_f) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action4(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(SDLK_r) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action5(id_);
				i = nullptr;
			}

		}

	}
	else {
		tr_->setVelX(0);
		tr_->setVelY(0);
	}

	if (keyboard->keyUpEvent())animator->setCurrentState(Animator::States::Idle);
}
