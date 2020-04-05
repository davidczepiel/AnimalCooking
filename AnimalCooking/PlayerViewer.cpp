#pragma once
#include "PlayerViewer.h"

void PlayerViewer::init()
{	
	tr_ = GETCMP1_(Transform);
	animator = GETCMP1_(Animator);

	animator->setCurrentState(Animator::State::Idle);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),tr_->getW(),tr_->getH()};

	if (animator->getCurrentState() == Animator::State::Idle)cout << "Idle" << endl;
	else if (animator->getCurrentState() == Animator::State::Walk)cout << "Walk" << endl;
	else if (animator->getCurrentState() == Animator::State::Attack)cout << "Attack" << endl;

	texture_->render(dest);
}
