#include "SDL_macros.h"
#include "ButtonBehaviourNC.h"
#include "Entity.h"
#include "AnimalCooking.h"
#include "ButtonRenderer.h"
#include "MapInfoBoxViewer.h"

ButtonBehaviourNC::ButtonBehaviourNC(Entity *infoBox, levelInfo info) : 
	Component(ecs::ButtonBehaviourNC),
	infoBox_(infoBox),
	ownerTransform_(nullptr),
	active_(nullptr),
	focusedByController_(nullptr),
	focusedByMouse_(nullptr),
	bRenderer_(nullptr),
	mapInfo_(info){
}

void ButtonBehaviourNC::init()
{
	ownerTransform_ = GETCMP1_(Transform);
}

void ButtonBehaviourNC::update()
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
				action();
				if (bRenderer_) bRenderer_->clicked();
			}
		}
		else focusedByMouse_ = false;
	}
}

//este metodo es llamado por el mando, cuando el boton esta siendo seleccionado y el mando le da a la A
void ButtonBehaviourNC::action() {
	infoBox_->getComponent<MapInfoBoxViewer>(ecs::MapInfoBoxViewer)->setCurrentInfoLevel(mapInfo_);
}
