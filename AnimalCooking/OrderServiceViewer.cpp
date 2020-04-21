#include "OrderServiceViewer.h"

void OrderServiceViewer::init()
{
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Repisa);
	position = RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY());

}

void OrderServiceViewer::draw()
{
	text->render(position);
}
