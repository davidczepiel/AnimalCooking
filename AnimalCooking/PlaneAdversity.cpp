#include "PlaneAdversity.h"
#include "IngredientsPool.h"
#include "Ingredient.h"

PlaneAdversity::PlaneAdversity(MultipleAdversityManager* mam) : 
	Adversity(mam), 
	planeTexture_(SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlaneShadow)),	
	blizzardTexture_(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Blizzard)),
	internalTimer(new Timer()),
	dir_(),
	planeRect_(),
	state_(),
	angle_(),
	force_(),
	velocity_(),
	isBlizzard_(false),
	blizzardDuration_(7000),
	blizzardLastAnimTick_(SDL_GetTicks()),
	blizzardFrameRate_(150),
	blizzardFrame_(0),
	alreadyInitialized(false){
}

void PlaneAdversity::StartPlane() {
	RandomNumberGenerator* rnd = SDLGame::instance()->getRandGen();
	int height = SDLGame::instance()->getWindowHeight();
	int width = SDLGame::instance()->getWindowWidth();

	planeRect_.w = isBlizzard_ ? SDLGame::instance()->getWindowWidth() : planeTexture_->getWidth();
	planeRect_.h = planeTexture_->getHeight();

	int n = rnd->nextInt(0, 8);
	switch (n)
	{
	case 0:
		planeRect_.x = 0 - planeRect_.w;
		planeRect_.y = height / 2 - planeRect_.h / 2;
		break;
	case 1:
		planeRect_.x = width;
		planeRect_.y = height / 2 - planeRect_.h / 2;
		break;
	case 2:
		planeRect_.x = width / 2 - planeRect_.w / 2;
		planeRect_.y = -planeRect_.h;
		break;
	case 3:
		planeRect_.x = width / 2 - planeRect_.w / 2;
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
		planeRect_.x = -planeRect_.w / 2;
		planeRect_.y = height - planeRect_.h / 2;
		break;
	case 7:
		planeRect_.x = width - planeRect_.w / 2;
		planeRect_.y = height;
		break;
	default:
		break;
	}

	dir_ = dirs_[n];
	angle_ = angles_[n];
	velocity_ = 1;
	force_ = 3;

	state_ = Going;
	if (!alreadyInitialized) {
		GETCMP2(SDLGame::instance()->getTimersViewer(), TimerViewer)->addTimer(internalTimer);
		alreadyInitialized = true;
	}
	internalTimer->timerReset();
	internalTimer->setTime(3500);
	internalTimer->timerStart();
}

bool PlaneAdversity::isPlaneOut()
{
	SDL_Rect windowRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	return (SDL_IntersectRect(&planeRect_, &windowRect, &windowRect) == SDL_FALSE);
}

void PlaneAdversity::moveEntities()
{
	for (Ingredient* i : multipleAdversityMngr_->getIngredientsPool()->getPool()) {
		i->setPos(i->getPos() + dir_ * force_);
	}

	Transform* playerTr_ = multipleAdversityMngr_->getTransformPlayer(Resources::Player1);
	playerTr_->setPos(playerTr_->getPos() + dir_ * force_);

	playerTr_ = multipleAdversityMngr_->getTransformPlayer(Resources::Player2);
	playerTr_->setPos(playerTr_->getPos() + dir_ * force_);
}

void PlaneAdversity::update() {
	//----------------caso ventisca------------------
	if (isBlizzard_) {
		Uint32 time = SDL_GetTicks();
		if (time - blizzardLastAnimTick_ >= blizzardFrameRate_) {
			blizzardLastAnimTick_ = time;
			blizzardFrame_++;
			if (blizzardFrame_ >= blizzardTexture_->getNumCols()) blizzardFrame_ = 0;
		}
	}
	//-------------------------------------------------

	internalTimer->update();

	if (internalTimer->isTimerEnd() && state_ == Going) {
		internalTimer->timerReset();
		internalTimer->setTime(7000);
		internalTimer->timerStart();
		velocity_ = 3;
		state_ = Pushing;
	}

	planeRect_.x += (dir_.getX() * velocity_);
	planeRect_.y += (dir_.getY() * velocity_);

	if (state_ == Going) return;

	if (isPlaneOut()) multipleAdversityMngr_->stopAdversity(ecs::PlaneAdversity);

	moveEntities();
}

void PlaneAdversity::draw() {
	if (!isBlizzard_) planeTexture_->render(planeRect_, angle_);
	else blizzardTexture_->renderFrame(planeRect_, 0, blizzardFrame_, angle_);
}

void PlaneAdversity::reset() {
	isBlizzard_ = false;
}

void PlaneAdversity::start()
{
	StartPlane();
}
