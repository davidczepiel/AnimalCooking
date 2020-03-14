#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "SDL_macros.h"
class SinkViewer :
	public Component
{
	Transform* tr;
	Texture* text;
public:
	void init()override;
	void draw() override;
};

