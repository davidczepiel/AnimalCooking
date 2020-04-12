#include "PlaneAdversity.h"
#include "IngredientsPool.h"
#include "Ingredient.h"

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();

	planeRect_ = RECT(SDLGame::instance()->getWindowWidth() / 2, SDLGame::instance()->getWindowHeight(), planeTexture_->getWidth(), planeTexture_->getHeight());
	velocity_ = rnd->nextInt(1, 5);
	force_ = rnd->nextInt(2, 7);
}

void PlaneAdversity::update() {
	planeRect_.y += velocity_;

	for (Ingredient* i : adversityMngr_->getIngredientsPool()->getPool()) {
		i->setPos(i->getPos() + Vector2D(0, force_));
	}
}

void PlaneAdversity::draw() {
	planeTexture_->render(planeRect_);
}

void PlaneAdversity::reset() {
	StartPlane();
}