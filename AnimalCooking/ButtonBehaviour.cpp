#include "SDL_macros.h"
#include "ButtonBehaviour.h"
#include "Entity.h"
#include "AnimalCooking.h"
#include "ButtonRenderer.h"

ButtonBehaviour::ButtonBehaviour(CallBackOnClick* callback,AnimalCooking* ac) : Component(ecs::ButtonBehaviour)
{
	callback_ = callback;
	ownerTransform_ = nullptr;
	active_ = true;
	focusedByMouse_ = false;
	focusedByController_ = false;
	ac_ = ac;
	bRenderer_ = nullptr;
}

void ButtonBehaviour::init()
{
	ownerTransform_ = GETCMP1_(Transform);
}

void ButtonBehaviour::update()
{
	if (active_) {
		InputHandler* ih = InputHandler::instance();
		Vector2D buttonPos = ownerTransform_->getPos();
		Vector2D mousePos = ih->getMousePos();

		SDL_Point mousePosition = { mousePos.getX(), mousePos.getY() };
		SDL_Rect buttonRect = RECT(buttonPos.getX(), buttonPos.getY(), ownerTransform_->getW(), ownerTransform_->getH());

		if (SDL_PointInRect(&mousePosition, &buttonRect)) {
			focusedByMouse_ = true;
			if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
				callback_(ac_); //Como la FSM esta en AnimalCooking necesito acceso a la instancia de animalcooking 
				if(bRenderer_) bRenderer_->clicked();
			}
		}
		else focusedByMouse_ = false;
	}
}

//este metodo es llamado por el mando, cuando el boton esta siendo seleccionado y el mando le da a la A
void ButtonBehaviour::action() {
	callback_(ac_); 
}
