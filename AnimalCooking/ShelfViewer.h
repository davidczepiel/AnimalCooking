#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL_macros.h"
#include "Shelf.h"
#include "Interactive.h"

class ShelfViewer : public Component	
{
public:
	ShelfViewer(Interactive* i, Texture* texture):Component(ecs::ShelfViewer), entity(i), text(texture) {}
	~ShelfViewer() {}

	void draw() override;
private:
	Interactive* entity;
	Texture* text;
};

