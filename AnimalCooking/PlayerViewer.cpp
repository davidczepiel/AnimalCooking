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

	// int(((game_->getTime() / animator->getAnimSpeed()) % 6)) --> usarlo como parametro para el metodo animate del Animator

	if (animator->getCurrentState() == Animator::States::Idle) cout << "Idle" << endl;
	else if (animator->getCurrentState() == Animator::States::Walk)  cout << "Walk" << endl;
	else if (animator->getCurrentState() == Animator::States::Attack) cout << "Attack" << endl;

	texture_->render(dest);
}
