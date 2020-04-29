#include "MainMenuPadNavigation.h"

MainMenuPadNavigation::MainMenuPadNavigation() : Component(ecs::MainMenuPadNavigation),
selectButton(nullptr), leftArrow(nullptr), rightArrow(nullptr), xAxisMoved(false), xDpadMoved(false), aButtonPressed(true)
{

}

void MainMenuPadNavigation::setSelectButton(Entity* e) {
	selectButton = e;
	GETCMP2(selectButton, MenuButtonRenderer)->setFocused(true);
}

void MainMenuPadNavigation::update() {
	//EN caso de que haya algún dispositivo conectado pregunto si ha pulsado algo para navegar
	//Si no hay ningún mando conectado no me interesa hacer nada
	if (GPadController::playerControllerConnected(0) || GPadController::playerControllerConnected(1)) {
		double dpad = 0;
		if (dPadUsed(&dpad) && !xDpadMoved) {
			xDpadMoved = true;
			changeFocus(dpad);
		}
		else if (xDpadMoved && dpad != 0)
			arrowFocused(dpad);

		else  if (xDpadMoved && dpad == 0)
			noArrowsFocused();

		//Si cualquiera de ellos está pulsando la A
		if (!aButtonPressed && (GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) ||
			GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A))) {
			if (selectButton != nullptr) {
				MenuButtonBehaviour* m = GETCMP2(selectButton, MenuButtonBehaviour);
				aButtonPressed = true;
				m->action();
			}
		}
		//Esta comprobación y el bool están preparados para que si vuelves del menu de mapa al menu principal
		//no te detecte instantaneamente que estas pulsando la A y vuelvas a meterte al mapa
		else if (aButtonPressed && (!GPadController::playerPressed(0, SDL_CONTROLLER_BUTTON_A) &&
			!GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_A)))
			aButtonPressed = false;
	}
}

bool MainMenuPadNavigation::dPadUsed(double* dpad) {
	//Si alguno de los dos player han pulsado alguna flecha, me muevo a la izquierda o a la derecha
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
	//EN caso de que ningun player se esté intentando desplazar por el menú
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
	//Tengo que poner el boton central como no seleccionado
	GETCMP2(selectButton, MenuButtonRenderer)->setFocused(false);
}
//Restauro las flechas
void MainMenuPadNavigation::noArrowsFocused() {
	xDpadMoved = false;
	GETCMP2(rightArrow, MenuButtonRenderer)->setFocused(false);
	GETCMP2(leftArrow, MenuButtonRenderer)->setFocused(false);
	//Tengo que volver a poner el botón central como que esta siendo seleccionado
	GETCMP2(selectButton, MenuButtonRenderer)->setFocused(true);

}