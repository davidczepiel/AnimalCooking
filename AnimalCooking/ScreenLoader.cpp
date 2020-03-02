#include "ScreenLoader.h"

ScreenLoader::ScreenLoader(Resources::Nivel nivel)
{
		Entity* menu_ = stage->addEntity();
		Entity* mensajes_ = stage->addEntity();

		barraCarga_ = stage->addEntity();

		buttonGo_ = stage->addEntity();

		resetResources(nivel);
}
		
void ScreenLoader::resetResources(Resources::Nivel nivel)
{
	SDLGame::instance()->load(nivel, GETCMP2(barraCarga_, BarraViewer));
	GETCMP2(buttonGo_, Active)->setActive();
}