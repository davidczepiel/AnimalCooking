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
	void pauseTimers();
	void resumeTimers();
	void resetTimers();
	void goToEndState(AnimalCooking* ac);
private:
	TimerViewer* timerViewer_;
};

