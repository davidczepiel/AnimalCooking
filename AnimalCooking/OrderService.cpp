#include "OrderService.h"

OrderService::OrderService(Vector2D pos, Transport* p1, Transport* p2, EntityManager* mng, ScoreManager* scoreManager): Entity(SDLGame::instance(), mng),Interactive(p1, p2)
{
	size_.setX(128*3);
	size_.setY(128);
	addComponent<OrderServiceViewer>(this);
	orderMngr =addComponent<OrderManager>(3,size_.getX()/3,pos,scoreManager);
	addComponent<OrderViewer>(size_.getX(),size_.getY(), Vector2D(0,0));
	addComponent<AIClient>();
	position_ = pos;
	size_ = Vector2D(128*3, 128);
}

void OrderService::action1(int id)
{
	//Obtengo el transport del jugador que me interesa
	Transport* player;
	if (id == 0)
		player = player1_;
	else
		player = player2_;

	//Pregunto si tiene un plato porque solo puedo trabajar con eso
	if (player->getObjectTypeInHands() == Resources::PickableType::Dish) {
		Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
		vector<Food*>* foods = &finalProduct->getFoodVector();
		//El plato debe tener 1 solo elemento dentro, porque si no sé que no está terminado
		if (foods->size()==1)
		{
			Resources::FoodType type = foods->at(0)->getType();
			//Pregunto al orderManager si a alquien lo ha pedido, si lo ha hecho borro el plato
			if (orderMngr->removeOrder(type,true)) {
				player->drop(false);
				finalProduct->clearFoods();
				delete finalProduct; //Llamo a la destructora del dish, la cual por si misma se elimina y se saca de la dishPool
			}
		}

	}

}
