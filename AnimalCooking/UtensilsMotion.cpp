#include "UtensilsMotion.h"

void UtensilsMotion::init() {
	pool_ = GETCMP1_(UtensilsPool)->getPool();
}

void UtensilsMotion::update() {
	for (Utensil* b : pool_) {
		cout << "b";
		if (b->inUse()) {
			b->update();
		}
	}
}