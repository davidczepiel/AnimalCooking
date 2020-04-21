#pragma once
#include "Component.h"
#include <list>

class Timer;

class TimerViewer : public Component
{
public:
	TimerViewer();
	virtual void draw() override;
	void deleteTimer(Timer* timerToDelete);
private:
	std::list<Timer*> timersList_;
};

