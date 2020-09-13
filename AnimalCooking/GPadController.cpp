#include "GPadController.h"
#include <SDL.h>

unique_ptr<GPadController> GPadController::instance_;


GPadController::GPadController() :player1_(nullptr),
player2_(nullptr)
{
	sleepTimerP1 = new Timer();
	sleepTimerP2 = new Timer();
	//GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(sleepTimerP1);
	//GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(sleepTimerP2);

}

void GPadController::update(SDL_Event& event) {

	sleepTimerP1->update();
	sleepTimerP2->update();

	if (sleepTimerP1->isTimerEnd())sleepTimerP1->timerReset();
	if (sleepTimerP2->isTimerEnd())sleepTimerP2->timerReset();

	//Si se ha a�adido un mando se lo asigno al player que le falte
	if (event.type == SDL_CONTROLLERDEVICEADDED) {
		if (player1_ == nullptr) {
			player1_ = SDL_GameControllerOpen(0);
			//SI los 2 players tienen mando el cursor no se deber�a de ver
			if (player1_ != nullptr && player2_ != nullptr)
				SDL_ShowCursor(0);
		}
		else if (player2_ == nullptr) {
			player2_ = SDL_GameControllerOpen(1);
			//SI los 2 players tienen mando el cursor no se deber�a de ver
			if (player1_ != nullptr && player2_ != nullptr)
				SDL_ShowCursor(0);
		}
	}
	//Si alg�n mando se ha desconectado vuelvo a pillar los mandos para ver cual tengo y cual no
	else if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
		player1_ = SDL_GameControllerOpen(0);
		player2_ = SDL_GameControllerOpen(1);
		//Significa que solo un player tiene mando y el cursor deberia de verse
		SDL_ShowCursor(1);
	}

	if (event.cbutton.type == SDL_CONTROLLERBUTTONDOWN) {
		lastButtonPressed_.first = true;
		lastButtonPressed_.second = (SDL_GameControllerButton)event.cbutton.button;
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

//Metodo llamado al principio de la ejecucion para conseguir mandos en caso de que est�n conectados
void GPadController::getPlayerGPADS() {
	player1_ = SDL_GameControllerOpen(0);
	player2_ = SDL_GameControllerOpen(1);

	//SI los 2 players tienen mando el cursor no se deber�a de ver
	if (player1_ != nullptr && player2_ != nullptr)
		SDL_ShowCursor(0);
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
		double value = SDL_GameControllerGetAxis(p, axis);
		if (abs(value) < m_joystickDeadZone) return (0);
		else return (value / 32678);
	}
	else return 0;
}


bool GPadController::playerPressed(int id, SDL_GameControllerButton button) {
	//Me hago con el mando que me interesa
	SDL_GameController* c;
	Timer* t;
	if (id == 0) {
		c = player1_;
		t = sleepTimerP1;
	}
	else {
		c = player2_;
		t = sleepTimerP2;
	}
	//Si hay un mando asi conectado pregunto por la tecla, si no hay mando, no hay pulsaci�n
	if (c != nullptr && c != NULL && !t->isStarted())
		return SDL_GameControllerGetButton(c, button);
	else
		return false;
}

void GPadController::sleepController(int player, int time)
{
	Timer* t;
	if (player == 0) {
		t = sleepTimerP1;
	}
	else {
		t = sleepTimerP2;
	}
	t->setTime(time);
	t->timerStart();
}

void GPadController::sleep(double time)
{
	sleepTimerP1->timerReset();
	sleepTimerP1->setTime(time);
	sleepTimerP1->timerStart();
}
