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
	keyUpdate();
	//joystickUpdate();
}

void PlayerController::joystickUpdate()
{
	GPadController* gpad = GPadController::instance();

	if (gpad->joysticksInitialised()) {
		double x = 0, y = 0;	//interactive
		//Axis------------------------
		if (gpad->xvalue(id_, 1) > 0 || gpad->xvalue(id_, 1) < 0)
		{
			tr_->setVelX(gpad->xvalue(id_, 1));
			x = gpad->xvalue(id_, 1);
		}
		else {
			tr_->setVelX(0);
		}
		if (gpad->yvalue(id_, 1) > 0 || gpad->yvalue(id_, 1) < 0)
		{
			tr_->setVelY(gpad->yvalue(id_, 1));
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
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
				i->action1(id_);
			i = nullptr;
		}
	}
	else {
		keyUpdate();
	}
}

void PlayerController::keyUpdate()
{
	InputHandler* keyboard = InputHandler::instance();

	int speed = 1;
	if (keyboard->keyDownEvent()) {
		//--------------------Movimiento
		int x = 0, y = 0;
		if (keyboard->isKeyDown(keys.up)) {
			tr_->setVelY(-speed); y = -1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.down)) {
			tr_->setVelY(speed); y = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		//else tr_->setVelY(0);

		if (keyboard->isKeyDown(keys.right)) {
			tr_->setVelX(speed);  x = 1;
			Interactive* i = selector_->getSelect();
			if (i != nullptr)
			{
				i->onMoved(id_);
				i = nullptr;
			}
		}
		else if (keyboard->isKeyDown(keys.left)) {
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

		//Estados de walk
		if (tr_->getVel().getX() != 0 || tr_->getVel().getY() != 0) 
		{ 
			if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Dish) animator->setCurrentState(Animator::States::WalkWithDish);
			else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
			{
				Utensil* u = static_cast<Utensil*>(transport->getObjectInHands());

				if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Knife) animator->setCurrentState(Animator::States::WalkWithKnife);
				else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Mace) animator->setCurrentState(Animator::States::WalkWithMace);
				else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Grater) animator->setCurrentState(Animator::States::WalkWithGrater);
				else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Net) animator->setCurrentState(Animator::States::WalkWithNet);
			}
			else animator->setCurrentState(Animator::States::Walk);
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
			if(transport->getObjectTypeInHands() == Resources::PickableType::Utensil)animator->setCurrentState(Animator::States::AttackWithKnife);
			
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
	else {
		tr_->setVelX(0);
		tr_->setVelY(0);	
	}

    //Estados de idle
	if (keyboard->keyUpEvent()) 
	{ 		
		if(transport->getObjectInHands()!=nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Dish) animator->setCurrentState(Animator::States::IdleWithDish); 
		else if (transport->getObjectInHands() != nullptr && transport->getObjectTypeInHands() == Resources::PickableType::Utensil)
		{
			Utensil* u = static_cast<Utensil*>(transport->getObjectInHands());

            if ( u!=nullptr && u->getUtensilType() == Resources::UtensilType::Knife) animator->setCurrentState(Animator::States::IdleWithKnife);
		    else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Mace) animator->setCurrentState(Animator::States::IdleWithMace);
		    else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Grater) animator->setCurrentState(Animator::States::IdleWithGrater);
		    else if (u != nullptr && u->getUtensilType() == Resources::UtensilType::Net) animator->setCurrentState(Animator::States::IdleWithNet);		
		}
		else animator->setCurrentState(Animator::States::Idle); 				
	}
}
