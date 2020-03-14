#include "SinkViewer.h"


void SinkViewer::init() {
	tr = GETCMP1_(Transform);
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fregadero);
}

void SinkViewer::draw() {
	text->render(RECT(tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH()));
}