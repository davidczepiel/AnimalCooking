#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL_macros.h"
#include "Shelf.h"
class ShelfViewer :
	public Component
{
	Transform* tr;
	Texture* text;
public:
	void init()override;
	void draw() override;
};

