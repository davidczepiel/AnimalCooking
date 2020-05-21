#include "SDL_macros.h"
#include "ButtonRenderer.h"
#include "Entity.h"

ButtonRenderer::ButtonRenderer(Texture* background, Texture* text) : Component(ecs::ButtonRenderer), active(true)
{
	background_ = background;
	text_ = text;

	ownerTransform_ = nullptr;
	buttonBehaviour_ = nullptr;

	clickedTime_ = 0;
	clickedTimeCD_ = 70;
}

void ButtonRenderer::init()
{
	ownerTransform_ = GETCMP1_(Transform);
	buttonBehaviour_ = GETCMP1_(ButtonBehaviour);
}

void ButtonRenderer::draw()
{
	if (active) {
		ButtonState state_ = ButtonState::Unfocushed;

		if (game_->getTime() - clickedTime_ < clickedTimeCD_)
			state_ = ButtonState::Cliked;
		else if (buttonBehaviour_->getFocusByController() || buttonBehaviour_->getFocusByMouse())
			state_ = ButtonState::Focushed;

		Vector2D pos = ownerTransform_->getPos();

		SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());
		background_->renderFrame(dest, 0, state_, ownerTransform_->getRot());

		if (text_ != nullptr)
		{
			Vector2D s = Vector2D(text_->getWidth() * (ownerTransform_->getH() - 10) / text_->getHeight(), ownerTransform_->getH() - 10);
			text_->render(RECT(dest.x + (dest.w / 2 - s.getX() / 2), dest.y + 5, s.getX(), s.getY()));
		}
	}
}
