#include "ButtonCheckRenderer.h"
#include "ButtonBehaviourNC.h"
#include "ButtonChangeOnClick.h"

#include "Entity.h"
#include "SDL_macros.h"

ButtonCheckRenderer::ButtonCheckRenderer(Texture* textFocused, Texture* textUnFocused) : Component(ecs::ButtonCheckRenderer),
	active(true), textFocused_(textFocused), textUnFocused_(textUnFocused),
	ownerTransform_(nullptr), buttonBehaviour_(nullptr), buttonBehaviourNC_(nullptr), buttonOnClick_(nullptr)
{
	checked_ = game_->getTextureMngr()->getTexture(Resources::Config_Tick);
	unChecked_ = game_->getTextureMngr()->getTexture(Resources::Config_UnTicked);
}

void ButtonCheckRenderer::init()
{
	ownerTransform_ = GETCMP1_(Transform);
	buttonBehaviour_ = GETCMP1_(ButtonBehaviour);
	buttonBehaviourNC_ = GETCMP1_(ButtonBehaviourNC);
	buttonOnClick_ = GETCMP1_(ButtonChangeOnClick);
}

void ButtonCheckRenderer::draw()
{
	if (active) { 
		//Tick
		Vector2D pos = ownerTransform_->getPos();
		SDL_Rect dest = RECT(pos.getX(), pos.getY(), unChecked_->getWidth(), unChecked_->getHeight());

		if (buttonOnClick_) {
			if (buttonOnClick_->getState() == 0) //UnChecked
				unChecked_->render(dest);
			else
				checked_->render(dest);
		}

		//Texto
		dest.x = dest.x + dest.w + 20;
		dest.w = textFocused_->getWidth();
		dest.h = textFocused_->getHeight();

		ButtonState state_ = ButtonState::Unfocushed;
		if (buttonBehaviour_ && (buttonBehaviour_->getFocusByController() || buttonBehaviour_->getFocusByMouse()) ||
			buttonBehaviourNC_ && (buttonBehaviourNC_->getFocusByController() || buttonBehaviourNC_->getFocusByMouse()))
			state_ = ButtonState::Focushed;

		if (state_ == ButtonState::Unfocushed)
			textUnFocused_->render(dest);
		else
			textFocused_->render(dest);	
	}
}


void ButtonCheckRenderer::clicked()
{
	if (buttonOnClick_) buttonOnClick_->changeState();
}