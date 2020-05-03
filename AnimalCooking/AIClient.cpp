#include "AIClient.h"
#include "Entity.h"
#include "OrderManager.h"
#include "GameConfig.h"

AIClient::AIClient() : AIClient(45, nullptr)
{
}

AIClient::AIClient(Uint32 deltaTimePerOrder, TimerViewer* tv) : Component(ecs::AIClient),
	orMngr_(nullptr), availableOrders_(), initialOrders_()
{
	t = new Timer();
	t->setTime(deltaTimePerOrder);

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
	int rng = game_->getRandGen()->nextInt() % availableOrders_.size();
	return availableOrders_[rng];
}
