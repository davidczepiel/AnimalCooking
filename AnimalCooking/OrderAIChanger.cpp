#include "OrderAIChanger.h"
#include "AIClient.h"
#include "Entity.h"

OrderAIChanger::OrderAIChanger(const initializer_list<int>& times, TimerViewer* tv) : Component(ecs::OrderAIChanger),
	groups_(), aiClient_(nullptr), timer(nullptr), times_(times) 
{
	groups_.push({Resources::FoodType::Salad, Resources::FoodType::Pizza5 + 1 });
	groups_.push({Resources::FoodType::Roast, Resources::FoodType::BakedChicken2 + 1});

	timer = new Timer();
	timer->setTime(times_.front() * 1000); times_.pop();
	tv->addTimer(timer);
}

void OrderAIChanger::init()
{
	aiClient_ = GETCMP1_(AIClient);
}

void OrderAIChanger::update()
{
	timer->update();
	if (timer->isTimerEnd()) {
		aiClient_->changeOrderGroup(groups_.front()); groups_.pop();
		timer->setTime(times_.front()); times_.pop();
		timer->timerReset();
		timer->timerStart();
	}
}
