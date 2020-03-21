#include "BinViewer.h"

void BinViewer::init() {
	tex_ = game_->getTextureMngr()->getTexture(Resources::Papelera);
	tr_ = GETCMP1_(Transform);
}

void BinViewer::draw()
{
	SDL_Rect rect;
	rect.x = tr_->getPos().getX(); rect.y = tr_->getPos().getY(); rect.w = tr_->getW(); rect.h = tr_->getH();

	tex_->render(rect);
}
