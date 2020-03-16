#include "Transport.h"
#include "Entity.h"

Transport::Transport() : Component(ecs::Transport)
{
	objInHands_ = nullptr;
	playerTransform_ = nullptr;
}

void Transport::pick(Pickable* obj)
{
	if (objInHands_ == nullptr)
		objInHands_ = obj;
	else swap(obj);
}

void Transport::drop()
{
	objInHands_ = nullptr;
}

void Transport::swap(Pickable* obj)
{
	objInHands_ = nullptr;
	objInHands_ = obj;
}

void Transport::init()
{
	playerTransform_ = GETCMP1_(Transform);
}

void Transport::update()
{	
	if (objInHands_ != nullptr && !(playerTransform_->getVel().getX() == 0 && playerTransform_->getVel().getY() == 0)) {

		int angle = atan2(playerTransform_->getVel().getY(), playerTransform_->getVel().getX());

		int centerX = playerTransform_->getPos().getX() + playerTransform_->getW() / 2;
		int centerY = playerTransform_->getPos().getY() + playerTransform_->getH() / 2;

		objInHands_->setPos(Vector2D(centerX, centerY) + Vector2D(0, -(playerTransform_->getH()/2)).rotate((angle*180)/M_PI));
	}

	/*if (objInHands_ != nullptr && !(playerTransform_->getVel().getX() == 0 && playerTransform_->getVel().getY() == 0)) {
		
		objInHands_->setPos(Vector2D(playerTransform_->getPos().getX() + playerTransform_->getW()/2 + playerTransform_->getVel().getX() * playerTransform_->getW()/2,
			playerTransform_->getPos().getY() + playerTransform_->getH()/2 + playerTransform_->getVel().getY() * playerTransform_->getH()/2));
	}*/
}

bool Transport::hasEmptyDish()
{
	/*if (dynamic_cast<Dish*>(objInHands_) != nullptr) {
		return static_cast<Dish*>(objInHands_)->isEmpty();
	}
	else return false;*/
	return false;
}
