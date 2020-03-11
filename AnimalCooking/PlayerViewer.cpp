#pragma once
#include "PlayerViewer.h"

void PlayerViewer::init()
{
	tr_ = GETCMP1_(Transform);
}

void PlayerViewer::draw()
{
	SDL_Rect dest = {tr_->getPos().getX(),tr_->getPos().getY(),64,64};
	texture_->render(dest);
}
