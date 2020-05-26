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
			if (t != nullptr) delete t;
			t = nullptr;
		}
	}
	virtual void draw() override;
	void deleteTimer(Timer* timerToDelete);
	void addTimer(Timer* timerToAdd);
	inline const std::list<Timer*>& getTimers() const { return timersList_; }
private:
	std::list<Timer*> timersList_;
};

