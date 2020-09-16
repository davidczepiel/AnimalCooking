#include "AIClient.h"
#include "Entity.h"
#include "OrderManager.h"
#include "GameConfig.h"

AIClient::AIClient() : AIClient(45, 45, nullptr)
{
}

AIClient::AIClient(Uint32 deltaTimePerOrder, Uint32 deltaTimeFirstOrder, TimerViewer* tv) : Component(ecs::AIClient),
	orMngr_(nullptr), availableOrders_(), initialOrders_(), allOrders_(false), group({ Resources::_FirstOfFoods_ + 1, Resources::_LastOfFoods_ })
{
	t = new Timer();
	t->setTime(deltaTimeFirstOrder);
	deltaTimePerOrder_ = deltaTimePerOrder;
	firstOrder_ = true;

	tv->addTimer(t);
}

void AIClient::init()
{
	orMngr_ = GETCMP1_(OrderManager);
}

void AIClient::update()
{
	t->update();
	for (auto& o : orMngr_->getOrders()) {
		if (o != nullptr) {
			o->update();
			if (o->getAnger() > 1) 
				orMngr_->removeOrder(o->getFinalProduct(), false);
		}
	}
	checkNewOrder();
}

void AIClient::checkNewOrder()
{
	if (t->isTimerEnd()) {
		if (!initialOrders_.empty()) { //Primero saco los pedidos en cierto orden, si quedan		
			if (firstOrder_) {
				t->setTime(deltaTimePerOrder_);
				firstOrder_ = false;
			}			
			orMngr_->addOrder(initialOrders_.front());
			initialOrders_.pop();
		}
		else {	
			orMngr_->addOrder(chooseRandomOrder());
		}	
		t->timerReset();
		t->timerStart();
	}
}

Resources::FoodType AIClient::chooseRandomOrder()
{
	return (allOrders_) ? 
		(Resources::FoodType)game_->getRandGen()->nextInt(group.first, group.second)
		: 
		availableOrders_[game_->getRandGen()->nextInt() % availableOrders_.size()];
}
