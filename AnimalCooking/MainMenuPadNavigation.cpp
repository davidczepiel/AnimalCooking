#include "MainMenuPadNavigation.h"

MainMenuPadNavigation::MainMenuPadNavigation() : Component(ecs::MainMenuPadNavigation),
selectButton(nullptr), leftArrow(nullptr), rightArrow(nullptr), xAxisMoved(false), aButtonPressed(true)
{
}

void MainMenuPadNavigation::setSelectButton(Entity* e) {
	selectButton = e;
	GETCMP2(selectButton, MenuButtonRenderer)->setFocused(true);
}

void MainMenuPadNavigation::update() {
	//Me hago con el gamePad
	GPadController* gpad = GPadController::instance();
	//SOlo hago si hay un pad conectado
	if (gpad->joysticksInitialised()) {
		//Valor en x del joystick izquierdo del jugador 1
		double xValue = gpad->xvalue(0, 1);
		if ((xValue > 0 || xValue < 0) && !xAxisMoved)
		{
			xAxisMoved = true;
			changeFocus(xValue);
		}
		else if (xAxisMoved && xValue != 0)
			arrowFocused(xValue);
		else  if (xAxisMoved && xValue == 0)
			noArrowsFocused();

		if (gpad->getButtonState(0, SDL_CONTROLLER_BUTTON_A) && !aButtonPressed) {
			if (selectButton != nullptr) {
				MenuButtonBehaviour* m = GETCMP2(selectButton, MenuButtonBehaviour);
				m->action();
			}
		}
		if (!gpad->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			aButtonPressed = false;
		}
	}

}

//Hago que la flecha de la izquierda o la flecha de la derecha cambien el  estado selectButton
void MainMenuPadNavigation::changeFocus(float xValue) {
	if (selectButton != nullptr) {
		if (xValue < 0) 	GETCMP2(leftArrow, MenuButtonBehaviour)->action();
		else if (xValue > 0) 	GETCMP2(rightArrow, MenuButtonBehaviour)->action();
	}
}

//HAgo que la flecha que corresponda tenga brilli brilli
void MainMenuPadNavigation::arrowFocused(double xValue) {
	if (xValue < 0) GETCMP2(leftArrow, MenuButtonRenderer)->setFocused(true);
	else GETCMP2(rightArrow, MenuButtonRenderer)->setFocused(true);
}
//Restauro las flechas
void MainMenuPadNavigation::noArrowsFocused() {
	xAxisMoved = false;
	GETCMP2(rightArrow, MenuButtonRenderer)->setFocused(false);
	GETCMP2(leftArrow, MenuButtonRenderer)->setFocused(false);
}