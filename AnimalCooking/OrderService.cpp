#include "OrderService.h"

OrderService::OrderService(Vector2D pos, Transport* p1, Transport* p2, EntityManager* mng, ScoreManager* scoreManager): Entity(SDLGame::instance(), mng),Interactive(p1, p2)
{
	size_.setX(128*3);
	size_.setY(128);
	addComponent<OrderServiceViewer>(this);
	addComponent<OrderManager>(3,size_.getX()/3,pos,scoreManager);
	addComponent<OrderViewer>(size_.getX(),size_.getY());
	//addComponent<AIClient>();
	position_ = pos;
	orderSent= nullptr;
	size_ = Vector2D(100, 100);
}

void OrderService::action1(int id)
{
	Transport* player;
	if (id == 0)
		player = player1_;
	else
		player = player2_;

	if (player->getObjectTypeInHands() == Resources::PickableType::Dish) {
		Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
		vector<Food*>* foods = &finalProduct->getFoodVector();
		if (foods->size()==1)
		{
			player->drop(false);
			//AIClients->recieveOrder(finalProduct);
		}

	}

}
