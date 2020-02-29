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

}
