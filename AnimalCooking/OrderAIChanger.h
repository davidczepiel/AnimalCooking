#pragma once
#include "Component.h"
#include <queue>
#include "Timer.h"
#include "TimerViewer.h"

class AIClient;
class OrderAIChanger : public Component
{
public:
	OrderAIChanger(const initializer_list<int>& times, TimerViewer* tv);

	void init() override;
	void update() override;

private:
	queue<std::pair<int, int>> groups_;
	AIClient* aiClient_;

	Timer* timer;
	queue<int> times_;
};

