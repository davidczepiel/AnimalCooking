#include "ShelfViewer.h"


void ShelfViewer::init() {
	tr=GETCMP1_(Transform);
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Repisa);
}

void ShelfViewer::draw() {
	text->render(RECT(tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH()));
}