#include "IngredientViewer.h"
#include "IngredientsPool.h"
#include "Entity.h"
#include "Ingredient.h"

void IngredientViewer::init() {
	pool_ = GETCMP1_(IngredientsPool);
}

void IngredientViewer::draw() {
	for (Ingredient* b : pool_->getPool()) {
		b->render();
	}
}