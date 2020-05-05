#include "PlaneAdversity.h"
#include "IngredientsPool.h"
#include "Ingredient.h"

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();
	int height = SDLGame::instance()->getWindowHeight();
	int width = SDLGame::instance()->getWindowWidth();

	planeTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Aceite);

	int n = rnd->nextInt(0, 8);

	switch (n)
	{
	case 0:
		planeRect_.x = 0;
		planeRect_.y = height / 2;
		break;
	case 1:
		planeRect_.x = width;
		planeRect_.y = height / 2;
		break;
	case 2:
		planeRect_.x = width / 2;
		planeRect_.y = 0;
		break;
	case 3:
		planeRect_.x = width / 2;
		planeRect_.y = height;
		break;
	case 4:
		planeRect_.x = 0;
		planeRect_.y = 0;
		break;
	case 5:
		planeRect_.x = width;
		planeRect_.y = 0;
		break;
	case 6:
		planeRect_.x = 0;
		planeRect_.y = height;
		break;
	case 7:
		planeRect_.x = width;
		planeRect_.y = height;
		break;
	default:
		break;
	}

	planeRect_.w = planeTexture_->getWidth();
	planeRect_.h = planeTexture_->getHeight();

	dir_ = dirs_[n];
	angle_ = angles_[n];
	velocity_ = 3;
	force_ = 1.5;

	state_ = Pasando;
	internalTimer.setTime(10000);
	internalTimer.timerStart();
}

void PlaneAdversity::update() {
	internalTimer.update();

	if (internalTimer.isTimerEnd()) {
		if (state_ == Pasando) {
			internalTimer.timerReset();
			internalTimer.setTime(3000);
			internalTimer.timerStart();
			state_ = Empujando;
		}
		else {
			multipleAdversityMngr_->stopAdversity(ecs::PlaneAdversity);
			return;
		}
	}

	planeRect_.x += (dir_.getX() * velocity_);
	planeRect_.y += (dir_.getY() * velocity_);

	if (state_ == Pasando) return;

	for (Ingredient* i : multipleAdversityMngr_->getIngredientsPool()->getPool()) {
		i->setPos(i->getPos() + dir_ * force_);		
	}
}

void PlaneAdversity::draw() {
	planeTexture_->render(planeRect_, angle_);
}

void PlaneAdversity::reset() {
	StartPlane();
}