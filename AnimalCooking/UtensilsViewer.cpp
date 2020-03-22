#include "UtensilsViewer.h"


void UtensilsViewer::init() {
	pool_ = &GETCMP1_(UtensilsPool)->getPool();
}

void UtensilsViewer::draw() {
	for (Utensil* b : *pool_) {
			b->render();
	}
}