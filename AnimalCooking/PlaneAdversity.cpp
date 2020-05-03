#include "PlaneAdversity.h"
#include "IngredientsPool.h"
#include "Ingredient.h"

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();
	int height = SDLGame::instance()->getWindowHeight();
	int width = SDLGame::instance()->getWindowWidth();

	planeTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Aceite);
	planeRect_ = RECT(rnd->nextInt(0, width), height, planeTexture_->getWidth(), planeTexture_->getHeight());
	double b = atan(((double)height / 2) / (double)abs(planeRect_.x + (planeTexture_->getWidth() / 2) - ((double)width / 2)));
	dir_ = Vector2D(planeRect_.x + (planeTexture_->getWidth() / 2) - ((double)SDLGame::instance()->getWindowWidth() / 2), planeRect_.y - ((double)SDLGame::instance()->getWindowHeight() / 2)).normalize();
	angle = b * 180 / 3.1416;
	if (planeRect_.x + (planeTexture_->getWidth() / 2) > (height / 2)) angle *= -1;
	velocity_ = rnd->nextInt(1, 5);
	force_ = 1;
}

void PlaneAdversity::update() {
	planeRect_.x -= (dir_.getX() * velocity_);
	planeRect_.y -= (dir_.getY() * velocity_);

	for (Ingredient* i : adversityMngr_->getIngredientsPool()->getPool()) {
		i->setPos(i->getPos() - dir_ * force_);		//delta time ¿?
	}
}

void PlaneAdversity::draw() {
	planeTexture_->render(planeRect_, angle);
}

void PlaneAdversity::reset() {
	StartPlane();
}

Vector2D PlaneAdversity::calculateDir() {
	Vector2D dir;
	return dir;
}