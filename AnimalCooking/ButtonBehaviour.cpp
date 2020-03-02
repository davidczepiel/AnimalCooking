#include "SDL_macros.h"
#include "ButtonBehaviour.h"

ButtonBehaviour::ButtonBehaviour(CallBackOnClick* callback) : Component(ecs::ButtonBehaviour)
{
	callback_ = callback;
	ownerTransform_ = nullptr;
}

void ButtonBehaviour::init()
{
	ownerTransform_ = GETCMP1_(Transform);
}

void ButtonBehaviour::update()
{
	InputHandler* ih = InputHandler::instance();
	Vector2D buttonPos = ownerTransform_->getPos();
	Vector2D mousePos = ih->getMousePos();
	
	SDL_Point mousePosition = { mousePos.getX(), mousePos.getY() };
	SDL_Rect buttonRect = RECT(buttonPos.getX(), buttonPos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

	if (SDL_PointInRect( &mousePosition, &buttonRect) && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
		callback_(game_); //Como la FSM esta en AnimalCooking necesito acceso a la instancia de animalcooking 
	}
}
