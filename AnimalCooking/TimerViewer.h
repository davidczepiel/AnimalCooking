#pragma once
#include "Component.h"
#include <list>

class Timer;

class TimerViewer : public Component
{
public:
	TimerViewer();
	~TimerViewer() {
		for (auto& t : timersList_) {
			delete t;
			t = nullptr;
		}
	}
	virtual void draw() override;
	void deleteTimer(Timer* timerToDelete);
	void addTimer(Timer* timerToAdd);
private:
	std::list<Timer*> timersList_;
};

