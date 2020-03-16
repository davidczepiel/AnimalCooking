#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Interactive.h"
#include "SDL_macros.h"
class SinkViewer :
	public Component
{
	Interactive* entity;
	Texture* text;
public:
	SinkViewer(Interactive* i) :Component(ecs::SinkViewer) { entity = i; }
	void init()override;
	void draw() override;
};

