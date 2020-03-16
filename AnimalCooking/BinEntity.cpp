#include "BinEntity.h"

void BinEntity::interactive(int player)
{
	Dish* d;
	if (Resources::Player1 == player) {
		d = dynamic_cast<Dish*>(player1_->getObjectInHands());
		if (d != nullptr) {
			d->clearDish(); //Limpiar el plato
		}
	}
	else {
		d = dynamic_cast<Dish*>(player2_->getObjectInHands());
		if (d != nullptr) {
			d->clearDish(); //Limpiar el plato
		}
	}
}
