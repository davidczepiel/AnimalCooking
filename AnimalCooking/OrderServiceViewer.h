#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Entity.h"
#include "SDL_macros.h"
class OrderServiceViewer :
	public Component
{
	Interactive* entity;
	Texture* text;
	SDL_Rect position;
public:
	OrderServiceViewer(Interactive* i) :Component(ecs::ShelfViewer) { entity = i; }
	void init()override;
	void draw() override;
};

