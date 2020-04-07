#pragma once
#include "PlayerViewer.h"

void PlayerViewer::init()
{	
	tr_ = GETCMP1_(Transform);
	animator = GETCMP1_(Animator);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),tr_->getW(),tr_->getH()};

	if (animator->getCurrentState() == Animator::States::Idle)  texture_->render(dest, animator->animate(texture_, int(((game_->getTime() / animator->getAnimSpeed()) % 6)), 0, 1, 6)); 
	else if (animator->getCurrentState() == Animator::States::Walk)  texture_->render(dest, animator->animate(texture_, int(((game_->getTime() / animator->getAnimSpeed()) % 6)), 0, 1, 6)); 
	else if (animator->getCurrentState() == Animator::States::Attack) texture_->render(dest, animator->animate(texture_, int(((game_->getTime() / animator->getAnimSpeed()) % 6)), 0, 1, 6));
}
