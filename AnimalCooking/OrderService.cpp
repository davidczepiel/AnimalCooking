#include "OrderService.h"
#include "GPadController.h"

OrderService::OrderService(Transport* p1, Transport* p2, EntityManager* mng, DishPool* dp) :
	Entity(SDLGame::instance(), mng), Interactive(p1, p2, nullptr), dp(dp), orderMngr(nullptr)
{
	feedbackVisual_ = nullptr;
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

			dp->removeDish(finalProduct);
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
		//El plato debe tener 1 solo elemento dentro, porque si no s� que no est� terminado
		if (finalProduct->getFoodVector().size() == 1)
		{
			return true;
		}
	}
	return false;
}


void OrderService::feedback(int id)
{
	if (!SDLGame::instance()->getOptions().showKeyToPress)
		return;

	Transport* player;
	if (id == 0) player = player1_;
	else player = player2_;

	if (player->getObjectTypeInHands() == Resources::PickableType::Dish) {

		Dish* finalProduct = static_cast<Dish*>(player->getObjectInHands());
		vector<Food*> foods = finalProduct->getFoodVector();
		if (!finalProduct->isEmpty())
		{
			Resources::FoodType type = foods.at(0)->getType();

			if (orderMngr->someOneWantsThis(type) && foods.size() == 1) {

				if (GPadController::instance()->playerControllerConnected(id))
					SDLGame::instance()->renderFeedBack(position_ + Vector2D(0, -size_.getY() / 2), "Deliver Order",
						SDL_GameControllerGetStringForButton(SDLGame::instance()->getOptions().players_gPadButtons[id].PICKUP));
				else
					SDLGame::instance()->renderFeedBack(position_ + Vector2D(0, -size_.getY() / 2), "Deliver Order",
						SDL_GetKeyName(SDLGame::instance()->getOptions().players_keyboardKeys[id].PICKUP));
			}
		}
	}
}

