#pragma once 
#include "Component.h"
#include <queue>
#include "Timer.h"
#include "TimerViewer.h"

class GameControl;
class GameControlLevelIngredientsChanger : public Component
{
public:
	GameControlLevelIngredientsChanger(const initializer_list<int>& times, TimerViewer* tv);

	void update() override;

	void setGameControl(GameControl* gC);

private:
	queue<std::vector<Resources::IngredientType>> groups_;
	GameControl* gControl_;

	Timer* timer;
	queue<int> times_;
};
