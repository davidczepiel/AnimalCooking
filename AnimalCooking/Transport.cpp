#include "Transport.h"
#include "Entity.h"

Transport::Transport() : Component(ecs::Transport)
{
	objInHands_ = nullptr;
	playerTransform_ = nullptr;
	emptyDish_ = false;
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
	if (objInHands_ != nullptr) { objInHands_->setSpeed(playerTransform_->getVel()); }
}

bool Transport::hasEmptyDish()
{
	if (dynamic_cast<Dish*>(objInHands_) != nullptr) {
		return static_cast<Dish*>(objInHands_)->isEmpty();
	}
	else return false;
}
