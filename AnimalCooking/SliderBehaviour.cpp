#include "SliderBehaviour.h"
#include "Entity.h"

void SliderBehaviour::init()
{
	sliderBackground = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SliderBackground);
	sliderMovePoint = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SliderMovPoint);
	transform = GETCMP1_(Transform);
}

void SliderBehaviour::update()
{
	
}
