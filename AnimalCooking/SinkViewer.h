#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Interactive.h"
#include "SDL_macros.h"
#include "Timer.h"
class SinkViewer :
	public Component
{
	Interactive* entity;
	Texture* text;
	Texture* textOn;
	bool onAction;
	Timer recoverNormalState;
public:
	SinkViewer(Interactive* i);
	void init()override;
	void draw() override;
	void update() override;
	void setOnAction(bool b);
};

