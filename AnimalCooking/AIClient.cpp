#include "AIClient.h"
#include "Entity.h"
#include "OrderManager.h"

AIClient::AIClient() : AIClient(45)
{
}

AIClient::AIClient(Uint32 deltaTimePerOrder) : Component(ecs::AIClient),
	deltaTimePerOrder_(deltaTimePerOrder), orMngr_(nullptr), availableOrders_(), initialOrders_(), lastOrderTime_(SDLGame::instance()->getTime())
{
}

void AIClient::init()
{
	orMngr_ = GETCMP1_(OrderManager);
}

void AIClient::update()
{
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
	if (game_->getTime() - lastOrderTime_ > deltaTimePerOrder_) {
		lastOrderTime_ = game_->getTime();
		if (!initialOrders_.empty()) { //Primero saco los pedidos en cierto orden, si quedan
			orMngr_->addOrder(initialOrders_.front());
			initialOrders_.pop();
		}
		else {	
			orMngr_->addOrder(chooseRandomOrder());
		}		
	}
}

Resources::FoodType AIClient::chooseRandomOrder()
{
	int rng = game_->getRandGen()->nextInt() % availableOrders_.size();
	return availableOrders_[rng];
}
