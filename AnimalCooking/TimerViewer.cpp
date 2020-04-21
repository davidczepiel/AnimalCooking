#include "TimerViewer.h"
#include "Timer.h"

TimerViewer::TimerViewer(): Component(ecs::TimerViewer)
{
}

void TimerViewer::draw()
{
	auto it = timersList_.begin();
	while (it != timersList_.end()) {
		(*it)->draw();
	}
}

void TimerViewer::deleteTimer(Timer* timerToDelete)
{
	timersList_.remove(timerToDelete);
}
