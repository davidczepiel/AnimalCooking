#include "BackGroundViewer.h"

void BackGroundViewer::draw()
{
	bg->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
}
