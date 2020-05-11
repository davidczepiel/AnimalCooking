#include "PlayerController.h"
#include "GameConfig.h"
#include "Utensil.h"

void PlayerController::init()
{
	tr_ = GETCMP1_(Transform);
	ir_ = GETCMP1_(InteractionRect);
	selector_ = GETCMP1_(Selector);
	attack_ = GETCMP1_(Attack);
	animator = GETCMP1_(Animator);
	animator->setCurrentState(Animator::States::Idle);
	transport = GETCMP1_(Transport);
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
	//Se establece la direccion para mostrar la animacion correspondiente
	if (!(x == 0 && y == 0)) animator->setDir(Vector2D(x, y));

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
		//Estados de attack
		if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
		{
			animator->getTimer().timerStart();
			setUtensilState(Animator::States::AttackWithKnife, Animator::States::AttackWithMace,
				Animator::States::AttackWithGrater, Animator::States::AttackWithNet);
		}
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

	//estados de walk
	if((Xvalue !=0 || Yvalue !=0 || animator->getTimer().isTimerEnd()) && !GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_X))setAnimState(Animator::States::WalkWithDishFood, Animator::States::WalkWithKnife,
		                                                                          Animator::States::WalkWithMace, Animator::States::WalkWithGrater,
	/*Estados de idle*/	                                                          Animator::States::WalkWithNet, Animator::Walk);
	else if(((Xvalue==0 && Yvalue==0) || animator->getTimer().isTimerEnd()) && !GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_X)) setAnimState(Animator::States::IdleWithDishFood, Animator::States::IdleWithKnife,
		                                                                                Animator::States::IdleWithMace, Animator::States::IdleWithGrater,
		                                                                                Animator::States::IdleWithNet, Animator::States::Idle);
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
	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		int x = 0, y = 0;
		if (keyboard->isKeyDown(keys.UP)) {
			tr_->setVelY(-speed); y = -1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.DOWN)) {
			tr_->setVelY(speed); y = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		//else tr_->setVelY(0);

		if (keyboard->isKeyDown(keys.RIGHT)) {
			tr_->setVelX(speed);  x = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.LEFT)) {
			tr_->setVelX(-speed); x = -1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		//else tr_->setVelX(0);

		ir_->setDir(x, y);
		//Se establece la direccion para mostrar la animacion correspondiente
		if(!(x==0 && y==0)) animator->setDir(Vector2D(x,y));                                                                                                       		

		//Estados de walk
		if ((tr_->getVel().getX() != 0 || tr_->getVel().getY() != 0) || animator->getTimer().isTimerEnd()) setAnimState(Animator::States::WalkWithDishFood, Animator::States::WalkWithKnife,
			Animator::States::WalkWithMace, Animator::States::WalkWithGrater,
			Animator::States::WalkWithNet, Animator::Walk);

		//--------------------Botones

		if (keyboard->isKeyDown(keys.PICKUP) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->action1(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(keys.ATTACK))
		{
			attack_->attack();

			//Estados de attack
			if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
			{
				animator->getTimer().timerStart();

				setUtensilState(Animator::States::AttackWithKnife, Animator::States::AttackWithMace, 
					            Animator::States::AttackWithGrater, Animator::States::AttackWithNet);				
			}						
		}

		if (keyboard->isKeyDown(keys.NEXT) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action2(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(keys.PREVIOUS) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action3(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(keys.OPEN) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action4(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(keys.FINISHER) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action5(id_);
				i = nullptr;
			}
		}
	}
	else 
    {
		tr_->setVelX(0);
		tr_->setVelY(0);
	}

    //Estados de idle
	if (keyboard->keyUpEvent() || animator->getTimer().isTimerEnd()) setAnimState(Animator::States::IdleWithDishFood, Animator::States::IdleWithKnife, 
		                                                                          Animator::States::IdleWithMace, Animator::States::IdleWithGrater, 
	                                                                              Animator::States::IdleWithNet, Animator::States::Idle);			
}


void PlayerController::setAnimState(Animator::States d, Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4, Animator::States s)
{
	if (transport->getObjectInHands() != nullptr && (transport->getObjectTypeInHands() == Resources::PickableType::Dish || transport->getObjectTypeInHands() == Resources::PickableType::Food)) animator->setCurrentState(d);
	else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil) setUtensilState(u1, u2, u3, u4);
	else animator->setCurrentState(s);
}

void PlayerController::setUtensilState(Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4)
{
	Utensil* u = static_cast<Utensil*>(transport->getObjectInHands());

	if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Knife) animator->setCurrentState(u1);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Mace) animator->setCurrentState(u2);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Grater) animator->setCurrentState(u3);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Net) animator->setCurrentState(u4);
}
