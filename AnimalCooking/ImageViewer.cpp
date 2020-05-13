#include "ImageViewer.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

void ImageViewer::init()
{
	transform_ = GETCMP1_(Transform);
}

void ImageViewer::draw()
{
	SDL_Rect rect = RECT(transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH());
	texture_->render(rect);
}
