#include "ButtonPadNavigation.h"
#include "GpadKeySwitcher.h"
#include "SliderBehaviour.h"
#include "ButtonBehaviourNC.h"
#include "ButtonBehaviour.h"

ButtonPadNavigation::ButtonPadNavigation() :Component(ecs::ButtonPadNavigation),
	xAxisMoved(false), 
	aButtonPressed(true), 
	focushing(false), 
	playerToListen(2),
focus(nullptr){
		
}

void ButtonPadNavigation::AddButton(Entity* e, Entity* up, Entity* down, Entity* left, Entity* right, bool posibleFocus)
{
	button* newButton = new button();
	newButton->e = e;
	newButton->up = up;
	newButton->down = down;
	newButton->right = right;
	newButton->left = left;
	newButton->posibleFocus = posibleFocus;

	buttons.push_back(newButton);

	if (buttons.size()>0 && focus == nullptr && buttons.at(buttons.size()-1) != nullptr ) {
		//Si el el primer boton en a�adirse le digo que esta en el foco
		if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1))) {

			ButtonBehaviour* b = GETCMP2(buttons.at(0)->e, ButtonBehaviour);
			if (b != nullptr) b->setFocusByController(true);
			else {
				ButtonBehaviourNC* b = GETCMP2(buttons.at(0)->e, ButtonBehaviourNC);
				if (b != nullptr)
					b->setFocusByController(true);
			}
		}
		focus = buttons.at(buttons.size()-1);
	}
	//EN caso de que lo que esté metiendo es un Button...NC le paso el padNAvigation para que mas  tarde sepa cambiar el foco en caso de ser necesario
	ButtonBehaviourNC* b = GETCMP2(buttons.at(buttons.size() - 1)->e, ButtonBehaviourNC);
	if (b != nullptr)b->setButtonPadNavigation(this);

}

void ButtonPadNavigation::update() {
	GPadController* gpad = GPadController::instance();
	if (playerToListen == 2) { //Si escucha a ambos
		if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->isAnyButtonJustPressed()) {
			horizontalInput();
			verticalInput();
			//Si cualquiera de ellos est� pulsando la A
			if (gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_A) ||
				gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_A)) {
				action();
			}
		}
	}
	else {
		if (gpad->playerControllerConnected(playerToListen) && gpad->isAnyButtonJustPressed()) {
			horizontalInput();
			verticalInput();
			if (gpad->playerPressed(playerToListen, SDL_CONTROLLER_BUTTON_A))
				action();
		}
	}
}

void ButtonPadNavigation::horizontalInput() {
	if (playerToListen == 2) {
		if (GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
			GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
			horizontalMove(-1);
		else if (GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
			GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
			horizontalMove(1);
	}
	else {
		if (GPadController::instance()->playerPressed(playerToListen, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
			horizontalMove(-1);
		else if (GPadController::instance()->playerPressed(playerToListen, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
			horizontalMove(1);
	}
}

void ButtonPadNavigation::verticalInput() {
	if (playerToListen == 2) {
		if (GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_UP) ||
			GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_UP))
			verticalMove(-1);
		else if (GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
			GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
			verticalMove(1);
	}
	else {
		if (GPadController::instance()->playerPressed(playerToListen, SDL_CONTROLLER_BUTTON_DPAD_UP))
			verticalMove(-1);
		else if (GPadController::instance()->playerPressed(playerToListen, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
			verticalMove(1);
	}
}

void ButtonPadNavigation::action() {

	if (focus->posibleFocus) {
		SliderBehaviour* s = GETCMP2(focus->e, SliderBehaviour);
		if (s != nullptr) {
			focushing = !focushing;
			s->setPadNavEnable(focushing); //Si estoy en un slider
		}
	}
	else {
		ButtonBehaviour* b = GETCMP2(focus->e, ButtonBehaviour);
		if (b != nullptr) b->action();
		else {
			ButtonBehaviourNC* bNC = GETCMP2(focus->e, ButtonBehaviourNC);
			bNC->action();
		}
	}
}

void ButtonPadNavigation::horizontalMove(double xValue)
{
	if (focushing && focus->posibleFocus) {
		GpadKeySwitcher* s = GETCMP2(focus->e, GpadKeySwitcher);
		if (s != nullptr) {
			if (xValue < 0) {
				if (focus->left != nullptr) {
					changeFocus(focus->left);
					GpadKeySwitcher* s = GETCMP2(focus->e, GpadKeySwitcher);
					if (s != nullptr) s->setFocushed(-1);
				}
			}
			else {
				if (focus->right != nullptr) {
					changeFocus(focus->right);
					GpadKeySwitcher* s = GETCMP2(focus->e, GpadKeySwitcher);
					if (s != nullptr) s->setFocushed(-1);
				}
			}
		}
	}
	else {
		if (xValue < 0) {
			if (focus->left != nullptr) {

				if (focus->posibleFocus) {
					SliderBehaviour* b = GETCMP2(focus->e, SliderBehaviour);
					if (b != nullptr) b->setFocused(true);
				}

				GpadKeySwitcher* s = GETCMP2(focus->e, GpadKeySwitcher);
				if (s != nullptr) s->setFocushed(-1);

				stopFocusButton(focus);
				changeFocus(focus->left);
			}
		}
		else {
			if (focus->right != nullptr) {

				if (focus->posibleFocus) {
					SliderBehaviour* b = GETCMP2(focus->e, SliderBehaviour);
					if (b != nullptr) b->setFocused(false);
				}

				GpadKeySwitcher* s = GETCMP2(focus->right, GpadKeySwitcher);
				if (s != nullptr) s->setFocushed(-1);

				stopFocusButton(focus);
				changeFocus(focus->right);
			}
		}
	}
}

void ButtonPadNavigation::verticalMove(double yValue)
{
	if (focus->posibleFocus) {
		GpadKeySwitcher* s = GETCMP2(focus->e, GpadKeySwitcher);
		if (s != nullptr) {
			s->addFocushed(yValue);
		}
		else {
			SliderBehaviour* b = GETCMP2(focus->e, SliderBehaviour);
			if (b != nullptr) {
				if (yValue > 0 && focus->down) changeFocus(focus->down);
				else if (yValue < 0 && focus->up) changeFocus(focus->up);
				b->setFocused(false);
			}
			b = GETCMP2(focus->e, SliderBehaviour);
			if (b != nullptr) b->setFocused(true);
		}
	}
	else {

		if (yValue > 0) {
			if (focus->down != nullptr) {
				SliderBehaviour* b = GETCMP2(focus->down, SliderBehaviour);
				if (b != nullptr) {
					b->setFocused(true);
				}

				stopFocusButton(focus);
				changeFocus(focus->down);
			}
		}
		else if (yValue < 0) {
			if (focus->up != nullptr) {
				SliderBehaviour* b = GETCMP2(focus->up, SliderBehaviour);
				if (b != nullptr) {
					b->setFocused(true);
				}

				stopFocusButton(focus);
				changeFocus(focus->up);
			}
		}
	}
}

void ButtonPadNavigation::resetNavigation()
{
	buttons.clear();
	focus->e = nullptr;
	focus->up = nullptr;
	focus->down = nullptr;
	focus->right = nullptr;
	focus->left = nullptr;
	focus = nullptr;
}

void ButtonPadNavigation::setFocusOn(Entity* e)
{
	if (e != nullptr) {
		ButtonBehaviour* b = GETCMP2(focus->e, ButtonBehaviour);
		ButtonBehaviourNC* c = GETCMP2(focus->e, ButtonBehaviourNC);

		//A mi focus actual le aviso de que ya no lo es
		if (b != nullptr)b->setFocusByController(false);
		if (c != nullptr)c->setFocusByController(false);

		int i = 0;
		while (i < buttons.size() && buttons.at(i)->e != e) {
			i++;
		}
		//Al nuevo focus, el que me ha llegado, le indico que ahora es el focus
		if (i < buttons.size() && buttons.at(i)->e != nullptr) {
			focus = buttons.at(i);
			b = GETCMP2(focus->e, ButtonBehaviour);
			c = GETCMP2(focus->e, ButtonBehaviourNC);
			if (b != nullptr)b->setFocusByController(true);
			if (c != nullptr)c->setFocusByController(true);
		}
	}
}

void ButtonPadNavigation::addButtonToAnExistingOne(Entity* e, Entity* up, Entity* down, Entity* left, Entity* right, Entity* wich, int fromWhere)
{
	//Creo el nuevo botón que quiero añadir
	button* nuevo = new button();
	nuevo->e = e;
	nuevo->up = up;
	nuevo->down = down;
	nuevo->left = left;
	nuevo->right = right;
	nuevo->posibleFocus = false;
	buttons.push_back(nuevo);

	//Busco el boton existente al que lo quiero unir y le aviso de que lo voy a conectar con uno nuevo
	int i = 0;
	while (i < buttons.size() && buttons.at(i)->e != wich) {
		i++;
	}
	switch (fromWhere){
	case 0 ://Arriba
		buttons.at(i)->up = e;
		break;
	case 1://Abajo
		buttons.at(i)->down = e;
		break;
	case 2: //Izquierda
		buttons.at(i)->left = e;
		break;
	case 3://Derecha
		buttons.at(i)->right = e;
		break;
	}

}

void ButtonPadNavigation::stopFocusButton(button* b)
{
	if (b->e != nullptr) {
		ButtonBehaviour* bh = GETCMP2(focus->e, ButtonBehaviour);
		if (bh) bh->setFocusByController(false);
		else {
			ButtonBehaviourNC* bh = GETCMP2(focus->e, ButtonBehaviourNC);
			if (bh) bh->setFocusByController(false);
		}
	}
}


void ButtonPadNavigation::changeFocus(Entity* e) {
	int i = 0;
	//Tengo que encontrar el struct con la misma entidad para m�s tarde poder seguyir navegando
	while (i < buttons.size() && buttons.at(i)->e != e)
		i++;
	focus = buttons.at(i);
	ButtonBehaviour* b = GETCMP2(focus->e, ButtonBehaviour);
	if (b) b->setFocusByController(true);
	else {
		ButtonBehaviourNC* nc = GETCMP2(focus->e, ButtonBehaviourNC);
		if (nc) nc->setFocusByController(true);
	}


}
