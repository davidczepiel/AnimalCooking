#include "FoodGiverViewer.h"
#include "SDL_macros.h"

void FoodGiverViewer::init()
{
	texture_ = entity_->getTexture();
	rect_ = RECT(entity_->getPos().getX(), entity_->getPos().getY(), entity_->getSize().getX(), entity_->getSize().getY());
}

void FoodGiverViewer::draw()
{
	texture_->render(rect_);
}