#include "InteractionRect.h"

void InteractionRect::init()
{
	tr_ = GETCMP1_(Transform);
	tx_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuadradoAux);
}

void InteractionRect::draw()
{
	SDL_Rect d = { pos_.getX(), pos_.getY(), size_.getX(),size_.getY() };
	tx_->render(d);
}

void InteractionRect::update()
{
	pos_.set(tr_->getPos().getX() +tr_->getW() / 2  + radius * dir_.getX() - size_.getX() / 2, 
			 tr_->getPos().getY() + radius * dir_.getY() + tr_->getH() / 2 - size_.getY() / 2 );
}
