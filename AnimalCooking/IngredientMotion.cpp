#include "IngredientMotion.h"
#include "IngredientsPool.h"
#include "Entity.h"
#include "Ingredient.h"

void IngredientMotion::init() {
	pool_ = GETCMP1_(IngredientsPool);
	ph = GETCMP1_(Physics);
}

void IngredientMotion::update() {
	for (Ingredient* b : pool_->getPool()) {
		SDL_Rect body;
		body.x = b->getPos().getX();
		body.y = b->getPos().getY();
		body.w = b->getWidth();
		body.h = b->getHeight();
		Vector2D vel = b->getVel();
		b->update();
		/*else {
			b->setPos(ph->ReadjustPos(b->getPos()));
		}*/
	}
}