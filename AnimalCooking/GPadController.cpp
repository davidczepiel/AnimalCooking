#include "GPadController.h"
#include <SDL.h>

unique_ptr<GPadController> GPadController::instance_;
SDL_GameController* GPadController::player1_ = nullptr;
SDL_GameController* GPadController::player2_ = nullptr;

GPadController::GPadController()
{
}

bool GPadController::playerDPAD(int id) {
	if (id == 0) {
		if (player1_ == nullptr) {
			SDL_GameController* g = SDL_GameControllerOpen(0);
			if (g != NULL) {
				player1_ = g;
				return true;
			}
			else return false;
		}
		else
			return true;
	}
	else {
		if (player2_ == nullptr) {
			SDL_GameController* g = SDL_GameControllerOpen(1);
			if (g != NULL) {
				player2_ = g;
				return true;
			}
			else return false;
		}
		else
			return true;
	}
}



//Desinicializamos los joysticks
void GPadController::clean()
{

}



double ::GPadController::getAxisX(int player, int axis) {
	SDL_GameController* p;
	if (player == 0)
		p = player1_;
	else
		p = player2_;
	double value = SDL_GameControllerGetAxis(p, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);

	if (abs(value) < m_joystickDeadZone) return (0);
	else return (value/32678);
}

double ::GPadController::getAxisY(int player, int axis) {
	SDL_GameController* p;
	if (player == 0)
		p = player1_;
	else
		p = player2_;
	double value = SDL_GameControllerGetAxis(p, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	if (abs(value) < m_joystickDeadZone) return (0);
	else 
		return (value / 32678);
}

bool GPadController::playerPressed(int id, SDL_GameControllerButton button) {
	SDL_GameController* c;
	if (id == 0)c = player1_;
	else c = player2_;
	return SDL_GameControllerGetButton(c, button);
}


void GPadController::ControllerButtonDown(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	switch (event.cbutton.button) {
	case SDL_CONTROLLER_BUTTON_A:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_A) = true;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_B) = true;
		break;
	case SDL_CONTROLLER_BUTTON_X:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_X) = true;
		break;
	case SDL_CONTROLLER_BUTTON_Y:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_Y) = true;
		break;

	}

}

void GPadController::ControllerButtonUp(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	switch (event.cbutton.button) {
	case SDL_CONTROLLER_BUTTON_A:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_A) = false;
		break;
	case SDL_CONTROLLER_BUTTON_B:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_B) = false;
		break;
	case SDL_CONTROLLER_BUTTON_X:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_X) = false;
		break;
	case SDL_CONTROLLER_BUTTON_Y:
		m_buttonStates[whichOne].at(SDL_CONTROLLER_BUTTON_Y) = false;
		break;

	}
}