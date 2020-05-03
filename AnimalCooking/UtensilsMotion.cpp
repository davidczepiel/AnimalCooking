#include "UtensilsMotion.h"

void UtensilsMotion::init() {
	pool_ = &GETCMP1_(UtensilsPool)->getPool();
}

void UtensilsMotion::update() {
	for (Utensil* b : (*pool_)) {
			b->update();
	}
}