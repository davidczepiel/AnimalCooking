#include "ButtonDirector.h"
#include "ButtonBehaviour.h"
#include "SDL_macros.h"

ButtonDirector::ButtonDirector() : Component(ecs::ButtonDirector)
{
}

void ButtonDirector::update()
{
	ButtonBehaviour* bh;
	for (int i = 0; i < buttons_.size(); i++) {
		bh = GETCMP2(buttons_.at(i), ButtonBehaviour);
		bh->update();
	}
}

void ButtonDirector::addButton(Entity* button)
{
	if ( GETCMP2(button, ButtonBehaviour) != nullptr) { //Comprobar que sea un boton
		buttons_.push_back(button);
	}
}

void ButtonDirector::clearButons()
{
	for (int i = 0; i < buttons_.size(); i++) {
		delete buttons_.at(i);
		buttons_.at(i) = nullptr;
	}

	buttons_.clear();
}
