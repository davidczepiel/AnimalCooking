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
	if(!ph->Collided(lugar))
	tr_->setPos(tr_->getPos() + tr_->getVel()*SPEED);
}
