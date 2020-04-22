#include "BinViewer.h"

void BinViewer::init() {
	tex_ = game_->getTextureMngr()->getTexture(Resources::TextureId::Papelera);
}

void BinViewer::draw()
{
	SDL_Rect rect;
	rect.x = binEnt_->getPos().getX(); rect.y = binEnt_->getPos().getY(); rect.w = binEnt_->getSize().getX(); rect.h = binEnt_->getSize().getY();

	tex_->render(rect);
}
