#pragma once
#include "State.h"
#include "Manager.h"
#include "TimerViewer.h"
#include <list>
class PlayState : public State
{
public:
	PlayState(EntityManager* em, TimerViewer* timers, AnimalCooking* ac) : State(em, ac), timerViewer_(timers) {
		SDLGame::instance()->getAudioMngr()->playMusic(Resources::AudioId::Level1);
	}
	void pauseTimers();
	void resumeTimers();
	void resetTimers();
	void goToEndState(AnimalCooking* ac);
	EntityManager* getEntityManager() { return stage; }
private:
	TimerViewer* timerViewer_;
};

