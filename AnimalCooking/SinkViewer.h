#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Interactive.h"
#include "SDL_macros.h"
#include "Timer.h"

class SinkViewer : public Component	
{	
public:
	SinkViewer(Interactive* i);
	~SinkViewer() {}

	void init()override;
	void draw() override;
	void update() override;

	void setOnAction(bool b);
private:
	Interactive* entity;
	Texture* text;
	Texture* textOn;
	Timer recoverNormalState;

	bool onAction;
};

