#include "PlayerMotion.h"
#include "Entity.h"

void PlayerMotion::init()
{
	tr_ = GETCMP1_(Transform);
	ph = GETCMP1_(Physics);
}

void PlayerMotion::update()
{
	if (!ph->Collided(tr_, SPEED))
		tr_->setPos(tr_->getPos() + tr_->getVel() * SPEED);
	else {
		//tr_->setPos(ph->ReadjustPos(tr_->getPos()) + ph->ReadjustVel(tr_->getVel()) * SPEED);
		ph->ReadjustVel(tr_, SPEED);
		tr_->setPos(tr_->getPos()+tr_->getVel()*SPEED);
	}
}
