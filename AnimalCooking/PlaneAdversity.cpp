#include "PlaneAdversity.h"

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();

	planeRect_ = RECT(SDLGame::instance()->getWindowWidth() / 2, SDLGame::instance()->getWindowHeight(), planeTexture_->getWidth(), planeTexture_->getHeight());
	velocity_ = rnd->nextInt(5, 10);
	force_ = 10.0;
}

void PlaneAdversity::update() {
	planeRect_.y += velocity_;

	for(Ingredient i : adversityMngr_->getIngredientsPool()->getPool())
}

void PlaneAdversity::draw() {

}

void PlaneAdversity::reset() {

}