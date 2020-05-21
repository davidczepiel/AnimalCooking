#include "Component.h"

Component::Component(ecs::CmpId id) :
		entity_(nullptr), //
		game_(SDLGame::instance()), //
		id_(id) //
{
}

Component::~Component() {
}
