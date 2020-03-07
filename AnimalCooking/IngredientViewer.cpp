#include "IngredientViewer.h"
#include "IngredientsPool.h"
#include "Entity.h"

void IngredientViewer::init() {
	pool_ = GETCMP1_(IngredientsPool)->getPool();
}

void IngredientViewer::draw() {
	for (Ingredient* b : pool_) {

		if (b->inUse()) {
			b->render();
		}
	}
}