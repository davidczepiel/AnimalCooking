#include "InteractionRect.h"
#include "GameConfig.h"

InteractionRect::InteractionRect(double casillaLength) : Component(ecs::InteractionRect), pos_(), dir_(), 
	size_(config::INTERACTION_RECT_SIZE_X * casillaLength, config::INTERACTION_RECT_SIZE_Y * casillaLength)
{
}

void InteractionRect::init()
{
	tr_ = GETCMP1_(Transform);
	tx_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::CuadradoAux);
}

void InteractionRect::draw()
{
	SDL_Rect d = { pos_.getX(), pos_.getY(), size_.getX(), size_.getY() };
	tx_->render(d);
}

void InteractionRect::update()
{
	if (!(dir_.getX() == 0 && dir_.getY() == 0))
		pos_.set(tr_->getPos().getX() + tr_->getW() / 2 + config::INTERACTION_RECT_RADIUS * dir_.getX() - size_.getX() / 2,
			tr_->getPos().getY() + config::INTERACTION_RECT_RADIUS * dir_.getY() + tr_->getH() / 2 - size_.getY() / 2);
}
