#pragma once
#include "SDL_macros.h"
#include "Component.h"
class BackGroundViewer :
	public Component
{
public:
	BackGroundViewer(Texture* bg):Component(ecs::BackGroundViewer),bg(bg){}
	void draw() override;
private:
	Texture* bg;
};

