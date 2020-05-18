#include "NameAsker.h"

void NameAsker::draw()
{
	bg->render(RECT(2 * casillaX, 2 * casillaY, 14 * casillaX, 7 * casillaY));
}

void NameAsker::init()
{
	bg = SDLGame::instance()->getTextureMngr()->getTexture(Resources::NameAsker);
	button = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button);
	casillaX = SDLGame::instance()->getCasillaX();
	casillaY = SDLGame::instance()->getCasillaY();
}
