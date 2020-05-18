#include "PlayerMotion.h"
#include "Entity.h"
#include "GameConfig.h"

void PlayerMotion::init()
{
	tr_ = GETCMP1_(Transform);
}

void PlayerMotion::update()
{
	tr_->setPos(tr_->getPos() + Vector2D(tr_->getVel().getX() * (config::PLAYER_SPEED * game_->getCasillaX() / 60)
	, tr_->getVel().getY() * (config::PLAYER_SPEED * game_->getCasillaY() / 60)));
}
