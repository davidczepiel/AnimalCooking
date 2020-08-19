#include "SliderRenderer.h"
#include "Entity.h"
#include "SDL_macros.h"

void SliderRenderer::init()
{
	sliderBackground_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Config_Slider);
	sliderSelectedBackground_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Config_SliderSelected);
	sliderMovePoint_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Config_SliderMovPoint);
	sliderSelectedMovePoint_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Config_SliderMovPointSelected);
	transform_ = GETCMP1_(Transform);
	sliderBehav_ = GETCMP1_(SliderBehaviour);
}

void SliderRenderer::draw()
{ 
	SDL_Rect moveRect = *sliderBehav_->getMovePointRect();

	if (sliderBehav_->getFocused())
		sliderSelectedBackground_->render(RECT(transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH()));
	else 
		sliderBackground_->render(RECT(transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH()));		
	
	if(sliderBehav_->getPadEnable() || sliderBehav_->getActive())
		sliderSelectedMovePoint_->render(RECT(moveRect.x - (moveRect.w / 2), moveRect.y - (moveRect.h / 2), moveRect.w, moveRect.h));
	else 
		sliderMovePoint_->render(RECT(moveRect.x - (moveRect.w / 2), moveRect.y - (moveRect.h / 2), moveRect.w, moveRect.h));
}
