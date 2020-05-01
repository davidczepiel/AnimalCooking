#include "TimerViewer.h"
#include "Timer.h"

TimerViewer::TimerViewer(): Component(ecs::TimerViewer), timersList_(std::list<Timer*>())
{
}

void TimerViewer::draw()
{
	auto it = timersList_.begin();
	while (it != timersList_.end()) {
		if(((*it)->isStarted()))(*it)->draw();
		++it;
	}
}

void TimerViewer::deleteTimer(Timer* timerToDelete)
{
	timersList_.remove(timerToDelete);
	delete timerToDelete;
}

void TimerViewer::addTimer(Timer* timerToAdd)
{
	timersList_.push_back(timerToAdd);
}
