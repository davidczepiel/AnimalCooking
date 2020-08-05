#include "DishFinisherViewer.h"

void DishFinisherViewer::draw()
{
	if (hasToPlay && frame_ < spritesheet_->getNumRows())
		spritesheet_->renderFrame(RECT(entity->getPos().getX(), entity->getPos().getY(), entity->getSize().getX(), entity->getSize().getY()), 0, frame_, 0);
}

void DishFinisherViewer::init()
{
	spritesheet_ = game_->getTextureMngr()->getTexture(Resources::Explosion);

}

void DishFinisherViewer::update()
{
	if (hasToPlay && game_->getTime() / config::ANIM_SPEED % spritesheet_->getNumCols() == 0) {
		//frame_ = int(((game_->getTime() / config::ANIM_SPEED) % spritesheet_->getNumCols()));
		frame_++;
		if (frame_ == spritesheet_->getNumCols())
			hasToPlay = false;
	}
	/*if (game_->getTime()) {
		frame_++;
	}*/
}

void DishFinisherViewer::play()
{
	hasToPlay = true;
	frame_ = 0;
}
