#include "ShelfViewer.h"


void ShelfViewer::init() {	
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Repisa);
}

void ShelfViewer::draw() {
	text->render(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()));
}