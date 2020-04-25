#include "ButtonPadNavigation.h"



ButtonPadNavigation::ButtonPadNavigation() :Component(ecs::ButtonPadNavigation), xAxisMoved(false), aButtonPressed(true)
{
}


void ButtonPadNavigation::AddButton(Entity* e, Entity* up, Entity* down, Entity* left, Entity* right)
{
	button newButton;
	newButton.e = e;
	newButton.up = up;
	newButton.down = down;
	newButton.right = right;
	newButton.left = left;
	buttons.push_back(newButton);
	if (buttons.size() == 1)
		focus = buttons.at(0);
}



void ButtonPadNavigation::update() {
	//Me hago con el gamePad
	GPadController* gpad = GPadController::instance();
	//SOlo hago si hay un pad conectado
	if (gpad->joysticksInitialised()) {
		//Valor en x del joystick izquierdo del jugador 1
		double xValue = gpad->xvalue(0, 1);
		double yValue = gpad->yvalue(0, 1);

		if ((xValue != 0 || yValue != 0) && !xAxisMoved)
		{
			if (abs(xValue) > abs(yValue))
				horizontalMove(xValue);
			else if (abs(xValue < abs(yValue)))
				verticalMove(yValue);
		}
		if (gpad->getButtonState(0, SDL_CONTROLLER_BUTTON_A) && !aButtonPressed) {
			action();
		}
		if (!gpad->getButtonState(0, SDL_CONTROLLER_BUTTON_A))
			aButtonPressed = false;
	}

}

void ButtonPadNavigation::action() {
	ButtonBehaviour* b = GETCMP2(focus.e, ButtonBehaviour);
	b->action();
}

void ButtonPadNavigation::horizontalMove(double xValue)
{
	if (xValue < 0) {
		if (focus.left != nullptr) {
			changeFocus(focus.left);
		}
	}
	else {
		if (focus.right != nullptr) {
			changeFocus(focus.right);
		}
	}
}
void ButtonPadNavigation::verticalMove(double yValue)
{
	if (yValue > 0) {
		if (focus.down != nullptr) {
			changeFocus(focus.down);
		}
	}
	else if (yValue < 0) {
		if (focus.up != nullptr) {
			changeFocus(focus.up);
		}
	}
}


void ButtonPadNavigation::changeFocus(Entity* e) {
	int i = 0;
	while (i < buttons.size() && buttons.at(i).e != e)
		i++;
	focus = buttons.at(i);
}