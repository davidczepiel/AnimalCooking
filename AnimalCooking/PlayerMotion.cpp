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
		SDL_Rect colision = ph->getLastCol();
		if (colision.w > colision.h) {
				int diference = abs(tr_->getPos().getY() - colision.y);
			if (colision.y > tr_->getPos().getY())
				tr_->setPos(Vector2D(tr_->getPos().getX(),tr_->getPos().getY()-colision.h));
			else
				tr_->setPos(Vector2D(tr_->getPos().getX(), tr_->getPos().getY()+ colision.h));
		}
		else {
			int diference = abs(tr_->getPos().getX() - colision.x);
			if (colision.x > tr_->getPos().getX())
				tr_->setPos(Vector2D(tr_->getPos().getX()-colision.w, tr_->getPos().getY()));
			else
				tr_->setPos(Vector2D(tr_->getPos().getX()+colision.w, tr_->getPos().getY()));
		}
	}
}
