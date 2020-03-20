#include "BinEntity.h"

void BinEntity::action1(int player)
{
	Dish* d;
	if (Resources::Player1 == player && player1_->getObjectInHands() != nullptr) {
		d = dynamic_cast<Dish*>(player1_->getObjectInHands());
		if (d != nullptr) {
			//Limpiar el plato
			std::vector<Food*> foodVector = d->getFoodVector();

			for (int i = 0; i < foodVector.size(); ++i) {
				foodVector[i]->Destroy();
			}
			foodVector.clear();
		}
	}
	else if(player2_->getObjectInHands() != nullptr) {
		d = dynamic_cast<Dish*>(player2_->getObjectInHands());
		if (d != nullptr) {
			//Limpiar el plato
			std::vector<Food*> foodVector = d->getFoodVector();

			for (int i = 0; i < foodVector.size(); ++i) {
				foodVector[i]->Destroy();
			}
			foodVector.clear();
		}
	}
}
