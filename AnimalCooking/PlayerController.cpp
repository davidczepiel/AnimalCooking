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
	double x = 0, y = 0;	

	//Axis------------------------
	double Xvalue = GPadController::instance()->getAxis(id_, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	if (Xvalue > 0 || Xvalue < 0)
		x = Xvalue;
	else 
		x = 0;

	double Yvalue = GPadController::instance()->getAxis(id_, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	if (Yvalue > 0 || Yvalue < 0)
		y = Yvalue;
	else 
		y = 0;

	Vector2D vel(x, y);
	vel = vel.normalize();
	if (ableToMove) {
		tr_->setVelY(speed * vel.getY());
		tr_->setVelX(speed * vel.getX());
	}
	else {
		inputVel.setX( vel.getX());
		inputVel.setY( vel.getY());
	}

	ir_->setDir(x, y);
	//Se establece la direccion para mostrar la animacion correspondiente
	if (!(x == 0 && y == 0)) { animator->setDir(Vector2D(x, y)); transport->setDir(Vector2D(x, y)); }
	
	//Botones-------------------------------
	if (ableToPress && GPadController::instance()->playerPressed(id_, buttons.PICKUP)) {
		ableToPress = false;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action1(id_);
			i = nullptr;
		}
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, buttons.OPEN)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action4(id_);
		i = nullptr;
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, buttons.ATTACK) && selector_ != nullptr) {
		attack_->attack();
		//Estados de attack
		if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
		{
			animator->getTimer().timerStart();
			if (!static_cast<Utensil*>(transport->getObjectInHands())->isDirty())
			setUtensilState(Animator::States::AttackWithKnife, Animator::States::AttackWithMace,
				            Animator::States::AttackWithGrater, Animator::States::AttackWithNet);
		}
		else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Bucket)
		{
			animator->getTimer().timerStart();

			if (static_cast<Bucket*>(transport->getObjectInHands())->getwaterStacks() > 0) animator->setCurrentState(Animator::States::UseCube);
		}
	}
	else if (ableToPress && GPadController::instance()->playerPressed(id_, buttons.FINISHER)) {
		Interactive* i = selector_->getSelect();
		if (i != nullptr)
			i->action5(id_);
		i = nullptr;
	}
	else if (!ableToPress&& padNotTouched())
		ableToPress = true;

	if (!dpadArrowsUsed && GPadController::instance()->playerPressed(id_, buttons.PREVIOUS) && selector_ != nullptr)
	{
		dpadArrowsUsed = true;
		Interactive* i = selector_->getSelect();
		if (i != nullptr) {
			i->action2(id_);
			i = nullptr;
		}
	}
	else if (!dpadArrowsUsed && GPadController::instance()->playerPressed(id_, buttons.NEXT) && selector_ != nullptr)
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
		                                                                          Animator::States::WalkWithMace, Animator::States::WalkWithGrater, Animator::States::WalkWithNet, Animator::States::Walk,	        	                                                                 
		                                                                          Animator::States::WalkWithDirtyKnife,Animator::States::WalkWithDirtyMace,Animator::States::WalkWithDirtyGrater,Animator::States::WalkWithDirtyNet, Animator::States::WalkWithFillCube, Animator::States::WalkWithEmptyCube);

	//Estados de idle
	else if(((Xvalue==0 && Yvalue==0) || animator->getTimer().isTimerEnd()) && !GPadController::instance()->playerPressed(id_, SDL_CONTROLLER_BUTTON_X)) setAnimState(Animator::States::IdleWithDishFood, Animator::States::IdleWithKnife,
		                                                                                Animator::States::IdleWithMace, Animator::States::IdleWithGrater,Animator::States::IdleWithNet, Animator::States::Idle,		                                                                                 
		                                                                                Animator::States::IdleWithDirtyKnife, Animator::States::IdleWithDirtyMace, Animator::States::IdleWithDirtyGrater, Animator::States::IdleWithDirtyNet, Animator::States::IdleWithFillCube, Animator::States::IdleWithEmptyCube);
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

	int x = 0, y = 0;

	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		if (keyboard->isKeyDown(keys.UP)) {
			movKeys.up = true;
		}
		else if (keyboard->isKeyDown(keys.DOWN)) {
			movKeys.down = true;
		}

		if (keyboard->isKeyDown(keys.RIGHT)) {
			movKeys.right = true;
		}
		else if (keyboard->isKeyDown(keys.LEFT)) {
			movKeys.left = true;
		}

		//--------------------Botones

		if(keyboard->isKeyDown(keys.PICKUP) && (SDLGame::instance()->getTime() - timerPickUp) > 150){
			pickAble = true; //Control de pickUp
			timerPickUp = SDLGame::instance()->getTime(); //Cogemos el timepo actual
		}
		if (pickAble && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->action1(id_);
				i = nullptr;		//Reseteamos interactuable
				pickAble = false;
			}
		}

		if (keyboard->isKeyDown(keys.ATTACK))
		{
			attack_->attack();

			//Estados de attack
			if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
			{
				animator->getTimer().timerStart();

				if(!static_cast<Utensil*>(transport->getObjectInHands())->isDirty())
				setUtensilState(Animator::States::AttackWithKnife, Animator::States::AttackWithMace,
					Animator::States::AttackWithGrater, Animator::States::AttackWithNet);
			}
			else if(transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Bucket)
			{
				animator->getTimer().timerStart();

				if (static_cast<Bucket*>(transport->getObjectInHands())->getwaterStacks() > 0) animator->setCurrentState(Animator::States::UseCube);
			}
		}

		if (keyboard->isKeyDown(keys.PREVIOUS) && selector_ != nullptr)
		{
			Interactive* i = selector_->getSelect();
			if (i != nullptr) {
				i->action2(id_);
				i = nullptr;
			}
		}
		if (keyboard->isKeyDown(keys.NEXT) && selector_ != nullptr)
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
	//Reseteamos control de tecla
	if (keyboard->keyUpEvent()) {
		if (keyboard->isKeyUp(keys.UP)) {
			movKeys.up = false;
		}
		if (keyboard->isKeyUp(keys.DOWN)) {
			movKeys.down = false;
		}
		if (keyboard->isKeyUp(keys.RIGHT)) {
			movKeys.right = false;
		}
		if (keyboard->isKeyUp(keys.LEFT)) {
			movKeys.left = false;
		}
		if (keyboard->isKeyUp(keys.PICKUP)) {
			pickAble = false;	
		}
	}

	if (movKeys.up) y = -1;
	else if (movKeys.down) y = 1;
	else y = 0;

	if (movKeys.right) x = 1;
	else if (movKeys.left) x = -1;
	else x = 0;

	Vector2D vel(x, y);
	vel = vel.normalize();

	if (ableToMove) {
		tr_->setVelY(speed * vel.getY());
		tr_->setVelX(speed * vel.getX());
	}
	else {
		inputVel.setX(speed* vel.getX());
		inputVel.setY(speed* vel.getY());
	}

	ir_->setDir(x, y);
	//Se establece la direccion para mostrar la animacion correspondiente
	if (!(x == 0 && y == 0)) { animator->setDir(Vector2D(x, y)); transport->setDir(Vector2D(x, y)); }

	//Estados de idle
	if (keyboard->keyUpEvent() || animator->getTimer().isTimerEnd()) setAnimState(Animator::States::IdleWithDishFood, Animator::States::IdleWithKnife,
		Animator::States::IdleWithMace, Animator::States::IdleWithGrater,
		Animator::States::IdleWithNet, Animator::States::Idle, 
		Animator::States::IdleWithDirtyKnife, Animator::States::IdleWithDirtyMace, Animator::States::IdleWithDirtyGrater, Animator::States::IdleWithDirtyNet,Animator::States::IdleWithFillCube, Animator::States::IdleWithEmptyCube);

	//Estados de walk
	if ((tr_->getVel().getX() != 0 || tr_->getVel().getY() != 0) || animator->getTimer().isTimerEnd()) setAnimState(Animator::States::WalkWithDishFood, Animator::States::WalkWithKnife,
		Animator::States::WalkWithMace, Animator::States::WalkWithGrater,
		Animator::States::WalkWithNet, Animator::States::Walk, 
		Animator::States::WalkWithDirtyKnife, Animator::States::WalkWithDirtyMace, Animator::States::WalkWithDirtyGrater, Animator::States::WalkWithDirtyNet, Animator::States::WalkWithFillCube, Animator::States::WalkWithEmptyCube);
}

void PlayerController::setAnimState(Animator::States d, Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4, Animator::States s, Animator::States u5, Animator::States u6, Animator::States u7, Animator::States u8, Animator::States b1, Animator::States b2)
{
	if (transport->getObjectInHands() != nullptr && (transport->getObjectTypeInHands() == Resources::PickableType::Dish || transport->getObjectTypeInHands() == Resources::PickableType::Food)) animator->setCurrentState(d);
	else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Bucket) setBucketState(b1, b2);
	else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil) 
	{ 
		if (static_cast<Utensil*>(transport->getObjectInHands())->isDirty()) setUtensilState(u5, u6, u7, u8);
		else setUtensilState(u1, u2, u3, u4); 
	}
	else animator->setCurrentState(s);
}

void PlayerController::setBucketState(Animator::States b1, Animator::States b2)
{
	if (static_cast<Bucket*>(transport->getObjectInHands())->getwaterStacks() > 0) animator->setCurrentState(b1); //cubo lleno
	else animator->setCurrentState(b2); //cubo vacio
}

void PlayerController::setUtensilState(Animator::States u1, Animator::States u2, Animator::States u3, Animator::States u4)
{
	Utensil* u = static_cast<Utensil*>(transport->getObjectInHands());

	if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Knife) animator->setCurrentState(u1);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Mace) animator->setCurrentState(u2);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Grater) animator->setCurrentState(u3);
	else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Net) animator->setCurrentState(u4);
	
}
