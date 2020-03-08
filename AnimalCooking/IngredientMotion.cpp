#include "IngredientMotion.h"
#include "IngredientsPool.h"
#include "Entity.h"
#include "Ingredient.h"

void IngredientMotion::init() {
	pool_ = GETCMP1_(IngredientsPool);
}

void IngredientMotion::update() {
	for (Ingredient* b : pool_->getPool()) {
		b->update();
	}
}