#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Interactive.h"
class DishFinisherViewer :
	public Component
{
public:
	DishFinisherViewer(Interactive* i) :Component(ecs::DishFinisherViewer),frame_(),spritesheet_(nullptr),hasToPlay(false),entity(i) {}
	void play();
	void draw() override;
	void init() override;
	void update() override;
private:
	Texture* spritesheet_;
	Interactive* entity;
	int frame_;
	bool hasToPlay;
};

