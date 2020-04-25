#pragma once
#include "State.h"
#include "Manager.h"
#include "Timer.h"
#include <list>
class PlayState : public State
{
public:

	PlayState(EntityManager* em, list<Timer*>timers, AnimalCooking* ac) : State(em, ac), timers(timers) {

	}
	//Al pausar el juego se llama a este método
	void pauseTimers();
	//al continuar el juego se debería llamar a este método(buscar dónde se continua)
	void resumeTimers();

private:
	list<Timer*> timers;
	static void goToEndState(AnimalCooking* ac);
};

