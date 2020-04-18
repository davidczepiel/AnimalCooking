#include "SliderRenderer.h"
#include "Entity.h"
#include "SDL_macros.h"

void SliderRenderer::init()
{
	sliderBackground_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SliderBackground);
	sliderMovePoint_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SliderMovPoint);
	transform_ = GETCMP1_(Transform);
	sliderBehav_ = GETCMP1_(SliderBehaviour);
}

void SliderRenderer::draw()
{ 
	sliderBackground_->render(RECT(transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH));

	SDL_Rect moveRect = *sliderBehav_->getMovePointRect();
	sliderMovePoint_->render(RECT(moveRect.x - (moveRect.w / 2), moveRect.y + (moveRect.h / 2), moveRect.w, moveRect.h));
}
