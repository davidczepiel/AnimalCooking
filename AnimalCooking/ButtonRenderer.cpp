#include "SDL_macros.h"
#include "ButtonRenderer.h"
#include "Entity.h"
#include "ButtonBehaviourNC.h"
#include "ButtonChangeOnClick.h"
#include "FSM.h"
#include "MapState.h"

ButtonRenderer::ButtonRenderer(Texture* background, Texture* text) : Component(ecs::ButtonRenderer), active(true)
{
	background_ = background;
	text_ = text;

	ownerTransform_ = nullptr;
	buttonBehaviour_ = nullptr;
	buttonBehaviourNC_ = nullptr;
	buttonOnClick_ = nullptr;

	clickedTime_ = 0;
	clickedTimeCD_ = 70;
}

void ButtonRenderer::init()
{
	ownerTransform_ = GETCMP1_(Transform);
	buttonBehaviour_ = GETCMP1_(ButtonBehaviour);
	buttonBehaviourNC_ = GETCMP1_(ButtonBehaviourNC);
	buttonOnClick_ = GETCMP1_(ButtonChangeOnClick);
}

void ButtonRenderer::draw()
{
	if (active) {
		ButtonState state_ = ButtonState::Unfocushed;

		if (game_->getTime() - clickedTime_ < clickedTimeCD_)
			state_ = ButtonState::Cliked;
		else if (buttonBehaviour_ && (buttonBehaviour_->getFocusByController() || buttonBehaviour_->getFocusByMouse()) || 
			buttonBehaviourNC_ && (buttonBehaviourNC_->getFocusByController() || buttonBehaviourNC_->getFocusByMouse()))
			state_ = ButtonState::Focushed;
		
		Vector2D pos = ownerTransform_->getPos();

		SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

		if (buttonOnClick_ != nullptr) {
			size_t i = buttonOnClick_->getState();
			switch (i)
			{
			case 0: //0 es de-activado
				state_ = ButtonState::Unfocushed;
				break;
			case 1: //1 es activado
				state_ = ButtonState::Focushed;
				break;
			default:
				break;
			}
		}

		background_->renderFrame(dest, 0, state_, ownerTransform_->getRot());
			
		if (text_ != nullptr)
		{
			Vector2D s = Vector2D(text_->getWidth() , text_->getHeight());
			if (s.getX() > ownerTransform_->getW() - 20) {
				s = Vector2D(ownerTransform_->getW() - 100, text_->getHeight());
			}

			text_->render(RECT(dest.x + (dest.w / 2 - s.getX() / 2), dest.y + dest.h / 2 - s.getY() / 2, s.getX(), s.getY()));
		}

		
	}	
}

void ButtonRenderer::clicked()
{
	clickedTime_ = game_->getTime(); 
	if (buttonOnClick_) buttonOnClick_->changeState();
}

void ButtonRendererMapArrow::init()
{
	ButtonRenderer::init();
}

void ButtonRendererMapArrow::draw()
{
	if (!available && active) {
		Vector2D pos = ownerTransform_->getPos();
		SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

		background_->renderFrame(dest, 0, 3, ownerTransform_->getRot());

		InputHandler* ih = InputHandler::instance();
		Vector2D buttonPos = ownerTransform_->getPos();
		Vector2D mousePos = ih->getMousePos();

		SDL_Point mousePosition = { mousePos.getX(), mousePos.getY() };
		SDL_Rect buttonRect = RECT(buttonPos.getX(), buttonPos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

		if (SDL_PointInRect(&mousePosition, &buttonRect) || buttonBehaviour_->getFocusByController()) {
			if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
				static_cast<MapState*>(game_->getFSM()->currentState())->notEnoughStarsWarning();
			}

			Vector2D pos = ownerTransform_->getPos();
			SDL_Rect dest = RECT(pos.getX(), pos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

			starsRequiredImageRect_ = RECT(dest.x + dest.w / 4, dest.y - (dest.w / 3), dest.w * 0.15, dest.w * 0.15);
			panelRect_ = RECT(dest.x + dest.w / 4 - 10, dest.y - (dest.w / 3) - 10, (dest.w * 0.5) + 20, (dest.w * 0.15) + 20);

			if (game_->getNumStars() < 10) 
				starsRequiredTextRect_ = RECT(dest.x + (dest.w * 0.25) + dest.w / 4, dest.y - (dest.w / 3), dest.w * 0.125, dest.w * 0.15);
			else 
				starsRequiredTextRect_ = RECT(dest.x + (dest.w * 0.25) + dest.w / 4, dest.y - (dest.w / 3), dest.w * 0.35, dest.w * 0.15);

			panel_->render(panelRect_);
			starsRequiredImage_->render(starsRequiredImageRect_);
			if(starsRequiredText_ != nullptr) starsRequiredText_->render(starsRequiredTextRect_);
		}

		return;
	}
	ButtonRenderer::draw();
}

void ButtonRendererMapArrow::updateText(int value)
{
	if (starsRequiredText_ != nullptr) delete starsRequiredText_;
	starsRequiredText_ = new Texture(game_->getRenderer(), to_string(value), game_->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor("#ffffffff"));
}
