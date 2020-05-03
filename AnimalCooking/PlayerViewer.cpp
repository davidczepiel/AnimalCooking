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

	//Aqui habra que mostrar las diferentes animaciones,de momento solo muestra la textura de cerdo
	if (animator->getCurrentState() == Animator::States::Idle) texture_->render(dest);
	else if (animator->getCurrentState() == Animator::States::Walk) texture_->render(dest);
	else if (animator->getCurrentState() == Animator::States::Attack) texture_->render(dest);

	
}
