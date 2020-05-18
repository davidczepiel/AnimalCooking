#pragma once
#include "Component.h"
#include "SDL_macros.h"
class NameAsker :
	public Component
{
public:
	NameAsker() : Component(ecs::nameAsker), bg(nullptr), button(nullptr),casillaX(0),casillaY(0) {}
	virtual void draw()override;
	virtual void init()override;
private:
	Texture* bg;
	Texture* button;
	double casillaX;
	double casillaY;
};

