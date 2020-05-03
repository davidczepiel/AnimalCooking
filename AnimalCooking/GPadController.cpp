#include "GPadController.h"
#include <SDL.h>

unique_ptr<GPadController> GPadController::instance_;


GPadController::GPadController()
{
	player1_ = nullptr;
	player2_ = nullptr;
}

void GPadController::update(SDL_Event& event) {
	//Si se ha añadido un mando se lo asigno al player que le falte
	if (event.type == SDL_CONTROLLERDEVICEADDED) {
		if (player1_ == nullptr) {
			player1_ = SDL_GameControllerOpen(0);
		}
		else if(player2_ == nullptr){
			player2_ = SDL_GameControllerOpen(1);
		}
	}
	//Si algún mando se ha desconectado vuelvo a pillar los mandos para ver cual teno y cual no
	else if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
		player1_ = SDL_GameControllerOpen(0);
		player2_ = SDL_GameControllerOpen(1);
	}
}

bool GPadController::playerControllerConnected(int id) {
	//Me hago con el player que interesa
	SDL_GameController* g;
	if (id == 0) g = player1_;
	else g = player2_;

	//Devuelvo si hay algun dispositivo o no
	if (g == nullptr || g == NULL)
		return false;
	else
		return true;
}

//Metodo llamado al principio de la ejecucion para conseguir mandos en caso de que estén conectados
void GPadController::getPlayerGPADS() {
	player1_ = SDL_GameControllerOpen(0);
	player2_ = SDL_GameControllerOpen(1);
}


double ::GPadController::getAxis(int player, SDL_GameControllerAxis axis) {
	//Me quedo con el player que me interesa
	SDL_GameController* p;
	if (player == 0)
		p = player1_;
	else
		p = player2_;
	//EN caso de que haya mando conectado pregunto por el valor
	//Si o hay mando devuelvo 0
	if (p != nullptr && p != NULL) {
		double value = SDL_GameControllerGetAxis(p,axis);
		if (abs(value) < m_joystickDeadZone) return (0);
		else return (value / 32678);
	}
	else return 0;
}


bool GPadController::playerPressed(int id, SDL_GameControllerButton button) {
	//Me hago con el mando que me interesa
	SDL_GameController* c;
	if (id == 0)c = player1_;
	else c = player2_;
	//Si hay un mando asi conectado pregunto por la tecla, si no hay mando, no hay pulsación
	if (c != nullptr && c != NULL)
		return SDL_GameControllerGetButton(c, button);
	else
		return false;
}


