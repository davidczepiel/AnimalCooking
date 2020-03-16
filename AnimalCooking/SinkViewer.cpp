#include "SinkViewer.h"


void SinkViewer::init() {
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Fregadero);
}

void SinkViewer::draw() {
	text->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(),entity->getSize().getY()));
}