#include "OrderService.h"

OrderService::OrderService(Transport* p1, Transport* p2, EntityManager* mng) :
	Entity(SDLGame::instance(), mng), Interactive(p1, p2, nullptr)
{
	feedbackVisual_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::EntregarPedido);
}

void OrderService::action1(int id)
{
	//Obtengo el transport del jugador que me interesa
	Transport* player;
	if (id == 0)
		player = player1_;
	else
		player = player2_;
	//Si lleva un plato con solo una cosa
	if (canService(id)) {
		//me quedo con el tipo de esa cosa que tiene el plato
		Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
		vector<Food*>* foods = &finalProduct->getFoodVector();
		Resources::FoodType type = foods->at(0)->getType();
		//Si se puede mandar al cliente me llevo el plato 
		if (orderMngr->removeOrder(type, true)) {
			Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
			player->drop(false);
			finalProduct->clearFoods();
			delete finalProduct; //Llamo a la destructora del dish, la cual por si misma se elimina y se saca de la dishPool
		}
	}

}

bool OrderService::canService(int id) {
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
		if (foods->size() == 1)
		{
			return true;
		}
	}
	return false;
}


void OrderService::feedback(int id)
{
	//Obtengo el transport del jugador que me interesa
	Transport* player;
	if (id == 0)
		player = player1_;
	else
		player = player2_;

	//Si el player tiene en la mano un plato con un solo elemento
	if (canService(id)) {
		Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
		vector<Food*>* foods = &finalProduct->getFoodVector();
		Resources::FoodType type = foods->at(0)->getType();
		//Pregunto al orderManager si a alquien lo ha pedido, si lo ha hecho dibujo el feedback
		if (orderMngr->someOneWantsThis(type)) {
			SDL_Rect r = RECT(position_.getX() -100, position_.getY() , 128, 32);
			feedbackVisual_->render(r);
		}
	}


}

