#include "PlayerMotion.h"
#include "Entity.h"

void PlayerMotion::init()
{
	tr_ = GETCMP1_(Transform);
	ph = GETCMP1_(Physics);
}

void PlayerMotion::update()
{
	SDL_Rect lugar;
	lugar.x = tr_->getPos().getX()+tr_->getVel().getX();
	lugar.y = tr_->getPos().getY() + tr_->getVel().getY();
	lugar.w = tr_->getW();
	lugar.h = tr_->getH();
	if (!ph->Collided(tr_))
		tr_->setPos(tr_->getPos() + tr_->getVel() * SPEED);
	else {
		tr_->setPos(ph->ReadjustPos(tr_->getPos()) + ph->ReadjustVel(tr_->getVel()) * SPEED);
		/*tr_->setVel(ph->ReadjustVel(tr_->getVel()));
		lugar.x = tr_->getPos().getX()+tr_->getVel().getX();
		lugar.y = tr_->getPos().getY()+tr_->getVel().getY();
		if (!ph->Collided(lugar, tr_->getVel()))
			tr_->setPos(tr_->setPos(tr_->getPos() + tr_->getVel() * SPEED););*/
	}
}
