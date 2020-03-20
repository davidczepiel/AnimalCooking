#include "BinEntity.h"

void BinEntity::action1(int player)
{
	Transport* playerTransport;

	player == Resources::Player1 ? playerTransport = player1_ : playerTransport = player2_;	//Se asigna el player correspondiente

	if (playerTransport->getObjectInHands() != nullptr && playerTransport->getObjectTypeInHands() == Resources::Dish) {
		//Limpiar el plato
		std::vector<Food*> foodVector = static_cast<Dish*>(playerTransport->getObjectInHands())->getFoodVector();

		for (int i = 0; i < foodVector.size(); ++i) {
			foodVector[i]->Destroy();
		}
		foodVector.clear();
	}

	playerTransport = nullptr;
}
