#include "Tool.h"
#include "GameLogic.h"

Bucket::Bucket(Transport* p1, Transport* p2) : Tool(p1, p2)
{
	waterStacks_ = 0;
	maxStacks_ = 3;
	lastAttack_ = SDL_GetTicks();
	attackRate_ = 700;
	attackHitBoxWidth_ = 0.8 * SDLGame::instance()->getCasillaX();
	attackHitBoxHeight_ = 0.5 * SDLGame::instance()->getCasillaY();
	rangeX_ = 0.8 * SDLGame::instance()->getCasillaX();
	rangeY_ = 0.8 * SDLGame::instance()->getCasillaY();
	myState = State::shelf;
	size_.setX(0.5 * SDLGame::instance()->getCasillaX());
	size_.setY(0.5 * SDLGame::instance()->getCasillaY());

	bucketTexture = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cubo);
}

void Bucket::attack(Vector2D dir)
{
	if (waterStacks_ > 0 && SDL_GetTicks() > lastAttack_ + attackRate_) {  //Control de que no se pueda espamear el ataque
		lastAttack_ = SDL_GetTicks();
		if (gameLogic != nullptr) { 
			Vector2D velNormalizada = speed_.normalize();
			SDL_Rect ataque;
			ataque.x = position_.getX() + (velNormalizada.getX() * rangeX_);
			ataque.y = position_.getY() + (velNormalizada.getY() * rangeY_);
			ataque.w = attackHitBoxWidth_;
			ataque.h = attackHitBoxHeight_;
			gameLogic->hitFire(ataque);
			waterStacks_--;
		}
	}
}

void Bucket::onPick()
{
	myState = State::playerHand;
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::PickUp, 0);
}

void Bucket::onDrop(bool onFloor)
{
	if (onFloor) {
		Pickable::onDrop(onFloor);
		myState = State::floor;
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Drop, 0);
	}
	else
		myState = State::shelf;
}

void Bucket::render()
{
	SDL_Rect rect = RECT(position_.getX(), position_.getY(), size_.getX(), size_.getY());

	if (myState != State::playerHand) {
		bucketTexture->render(rect);
	}
}


