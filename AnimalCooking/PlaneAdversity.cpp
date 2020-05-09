#include "PlaneAdversity.h"
#include "IngredientsPool.h"
#include "Ingredient.h"

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();
	int height = SDLGame::instance()->getWindowHeight();
	int width = SDLGame::instance()->getWindowWidth();

	planeTexture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlaneShadow);

	int n = rnd->nextInt(0, 8);
	n = 1;
	switch (n)
	{
	case 0:
		planeRect_.x = 0 - planeRect_.w;
		planeRect_.y = height / 2 - planeRect_.h / 2;
		break;
	case 1:
		planeRect_.x = width;
		planeRect_.y = height / 2 - planeRect_.y / 2;
		break;
	case 2:
		planeRect_.x = width / 2 - planeRect_.w / 2;
		planeRect_.y = 0 - planeRect_.h;
		break;
	case 3:
		planeRect_.x = width / 2 - planeRect_.x / 2;
		planeRect_.y = height;
		break;
	case 4:
		planeRect_.x = 0 - planeRect_.w;
		planeRect_.y = 0 - planeRect_.h;
		break;
	case 5:
		planeRect_.x = width;
		planeRect_.y = 0 - planeRect_.h;
		break;
	case 6:
		planeRect_.x = 0;
		planeRect_.y = height + planeRect_.h / 2;
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
	velocity_ = 1;
	force_ = 1.5;

	state_ = Pasando;
	internalTimer.timerReset();
	internalTimer.setTime(8500);
	internalTimer.timerStart();
}

bool PlaneAdversity::isPlaneOut()
{
	SDL_Rect windowRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	return (SDL_IntersectRect(&planeRect_, &windowRect, &windowRect) == SDL_FALSE);
}

void PlaneAdversity::update() {
	internalTimer.update();

	if (internalTimer.isTimerEnd() && state_ == Pasando) {
		internalTimer.timerReset();
		internalTimer.setTime(7000);
		internalTimer.timerStart();
		velocity_ = 3;
		state_ = Empujando;
	}

	planeRect_.x += (dir_.getX() * velocity_);
	planeRect_.y += (dir_.getY() * velocity_);

	if (state_ == Pasando) return;

	if (isPlaneOut()) multipleAdversityMngr_->stopAdversity(ecs::PlaneAdversity);

	for (Ingredient* i : multipleAdversityMngr_->getIngredientsPool()->getPool()) {
		i->setPos(i->getPos() + dir_ * force_);		
	}

	Transform* playerTr_ = multipleAdversityMngr_->getTransformPlayer(Resources::Player1);
	playerTr_->setPos(playerTr_->getPos() + dir_ * force_);

	playerTr_ = multipleAdversityMngr_->getTransformPlayer(Resources::Player2);
	playerTr_->setPos(playerTr_->getPos() + dir_ * force_);
}

void PlaneAdversity::draw() {
	planeTexture_->render(planeRect_, angle_);
}

void PlaneAdversity::reset() {
	StartPlane();
}