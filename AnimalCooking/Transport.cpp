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
	if (objInHands_ != nullptr) { objInHands_->setSpeed(playerTransform_->getVel()); }
}
