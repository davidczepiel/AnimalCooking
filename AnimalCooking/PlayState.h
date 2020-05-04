#pragma once
#include "State.h"
#include "Manager.h"
#include "TimerViewer.h"
#include <list>
class PlayState : public State
{
public:

	PlayState(EntityManager* em, TimerViewer* timers, AnimalCooking* ac) : State(em, ac), timerViewer_(timers) {

	}
	//Al pausar el juego se llama a este método
	void pauseTimers();
	//al continuar el juego se debería llamar a este método(buscar dónde se continua)
	void resumeTimers();

	void resetTimers();
	void goToEndState(AnimalCooking* ac,int score,int maxScore);
private:
	TimerViewer* timerViewer_;
};

