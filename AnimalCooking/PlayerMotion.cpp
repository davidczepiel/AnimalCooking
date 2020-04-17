#include "PlayerMotion.h"
#include "Entity.h"

void PlayerMotion::init()
{
	tr_ = GETCMP1_(Transform);
}

void PlayerMotion::update()
{
	tr_->setPos(tr_->getPos() + tr_->getVel() * SPEED);
}
