#include "InteractionRect.h"
#include "GameConfig.h"

InteractionRect::InteractionRect() : Component(ecs::InteractionRect), pos_(), dir_(), 
	size_(config::INTERACTION_RECT_SIZE_X * SDLGame::instance()->getCasillaX(), config::INTERACTION_RECT_SIZE_Y * SDLGame::instance()->getCasillaY()),
	radius(config::INTERACTION_RECT_RADIUS * SDLGame::instance()->getCasillaY())
{
}

void InteractionRect::init()
{
	tr_ = GETCMP1_(Transform);	
}

void InteractionRect::update()
{
	if (!(dir_.getX() == 0 && dir_.getY() == 0))
		pos_.set(tr_->getPos().getX() + tr_->getW() / 2 + radius * dir_.getX() - size_.getX() / 2,
			tr_->getPos().getY() + radius * dir_.getY() + tr_->getH() / 2 - size_.getY() / 2);
}
