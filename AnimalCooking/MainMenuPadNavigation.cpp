#include "MainMenuPadNavigation.h"

MainMenuPadNavigation::MainMenuPadNavigation() : Component(ecs::MainMenuPadNavigation),
selectButton(nullptr), leftArrow(nullptr), rightArrow(nullptr), xAxisMoved(false), xDpadMoved(false), aButtonPressed(true)
{
	if (GPadController::playerDPAD(0) || GPadController::playerDPAD(1)) someDpadConnected = true;
	else someDpadConnected = false;
}

void MainMenuPadNavigation::setSelectButton(Entity* e) {
	selectButton = e;
	GETCMP2(selectButton, MenuButtonRenderer)->setFocused(true);
}

void MainMenuPadNavigation::update() {
	if (someDpadConnected) {

		//Valor en x del joystick izquierdo del jugador 1
		double dpad = 0;
		if (dPadUsed(&dpad) && !xDpadMoved) {
			xDpadMoved = true;
			changeFocus(dpad);
		}
		/*	double xValue = gpad->xvalue(0, 1);
			if ((xValue > 0 || xValue < 0) && !xAxisMoved && !xDpadMoved)
			{
				xAxisMoved = true;
				changeFocus(xValue);
			}*/
			//else if (xAxisMoved && xValue != 0)
			//	arrowFocused(xValue);
		else if (xDpadMoved && dpad != 0)
			arrowFocused(dpad);

		else  if (xDpadMoved && dpad == 0)
			noArrowsFocused();

		if (!aButtonPressed && (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) ||
			GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A))) {
			if (selectButton != nullptr) {
				MenuButtonBehaviour* m = GETCMP2(selectButton, MenuButtonBehaviour);
				aButtonPressed = true;
				m->action();
			}
		}
		else if (aButtonPressed && (!GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) ||
			!GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A)))
			aButtonPressed = false;
	}
}

bool MainMenuPadNavigation::dPadUsed(double* dpad) {
	if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
		*dpad = -1;
		return true;
	}
	else if (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
		GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
		*dpad = 1;
		return true;
	}
	else
		return false;
}

bool MainMenuPadNavigation::dPadNotUsed() {
	if (!GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT) &&
		!GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) &&
		!GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_LEFT) &&
		!GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		return true;
	else
		return false;

}

//Hago que la flecha de la izquierda o la flecha de la derecha cambien el  estado selectButton
void MainMenuPadNavigation::changeFocus(float xValue) {
	if (xValue < 0) 	GETCMP2(leftArrow, MenuButtonBehaviour)->action();
	else if (xValue > 0) 	GETCMP2(rightArrow, MenuButtonBehaviour)->action();
}

//HAgo que la flecha que corresponda tenga brilli brilli
void MainMenuPadNavigation::arrowFocused(double xValue) {
	if (xValue < 0) GETCMP2(leftArrow, MenuButtonRenderer)->setFocused(true);
	else GETCMP2(rightArrow, MenuButtonRenderer)->setFocused(true);
}
//Restauro las flechas
void MainMenuPadNavigation::noArrowsFocused() {
	xDpadMoved = false;
	GETCMP2(rightArrow, MenuButtonRenderer)->setFocused(false);
	GETCMP2(leftArrow, MenuButtonRenderer)->setFocused(false);
}