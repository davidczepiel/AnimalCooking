#include "SliderBehaviour.h"
#include "Entity.h"
#include "SDL_macros.h"

void SliderBehaviour::init()
{
	transform = GETCMP1_(Transform);

	rectMovePoint.x = transform->getPos().getX() + (transform->getW() / 2);
	rectMovePoint.y = transform->getPos().getY() + (transform->getH() / 2);
	rectMovePoint.w = (int)(transform->getW() / 5);
	rectMovePoint.h = transform->getH() * 2;
}

void SliderBehaviour::update()
{
	InputHandler* ih = InputHandler::instance();
	SDL_Point mousePosition = { ih->getMousePos().getX(), ih->getMousePos().getY() };
	SDL_Rect rect = RECT(rectMovePoint.x - (rectMovePoint.w / 2), rectMovePoint.y - (rectMovePoint.h / 2), rectMovePoint.w, rectMovePoint.h);

	if (!active && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && SDL_PointInRect(&mousePosition, &rect))
		active = true;
	else if (active && ih->mouseButtonUpEvent())
		active = false;

	if (active){
		if (mousePosition.x >= transform->getPos().getX() && mousePosition.x <= transform->getPos().getX() + transform->getW()) 
			rectMovePoint.x = mousePosition.x;
		else if(mousePosition.x < transform->getPos().getX())
			rectMovePoint.x = transform->getPos().getX();
		else 
			rectMovePoint.x = transform->getPos().getX() + transform->getW();

		value = (rectMovePoint.x - transform->getPos().getX()) / transform->getW();
	}
}
