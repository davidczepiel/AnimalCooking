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
	GPadController* gpad = GPadController::instance();
	if (GPadController::playerControllerConnected(0) || GPadController::playerControllerConnected(1)) {
		horizontalInput();
		verticalInput();
		if ((GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) ||
			GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A))
			&& !aButtonPressed) {
			action();
		}
		if (!GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) &&
			!GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A))
			aButtonPressed = false;
	}
}

void ButtonPadNavigation::horizontalInput() {
	if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		horizontalMove(-1);
	else if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		horizontalMove(1);
}

void ButtonPadNavigation::verticalInput() {
	if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_UP))
		horizontalMove(-1);
	else if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		verticalMove(1);
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