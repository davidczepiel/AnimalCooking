#include "SDL_macros.h"
#include "ButtonRenderer.h"
#include "Entity.h"

ButtonRenderer::ButtonRenderer(Texture* background, Texture* text): Component(ecs::ButtonRenderer)
{
	background_ = background;
	text_ = text;

	ownerTransform_ = nullptr;
	buttonBehaviour_ = nullptr;
}

void ButtonRenderer::init()
{
	ownerTransform_ = GETCMP1_(Transform);
	buttonBehaviour_ = GETCMP1_(ButtonBehaviour);
}

void ButtonRenderer::draw()
{
	//if (buttonBehaviour_->isActive()) {
		Vector2D pos = ownerTransform_->getPos();

		SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());
		background_->render(dest,ownerTransform_->getRot());
		if (text_ != nullptr)
			text_->render(dest);
	}

