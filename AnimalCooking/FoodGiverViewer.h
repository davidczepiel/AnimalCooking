#pragma once

#include "Component.h"
#include "FoodGiver.h"

class FoodGiverViewer : public Component
{
private:
	FoodGiver* entity_;
	Texture* texture_;
	SDL_Rect rect_;

public:
	FoodGiverViewer(FoodGiver* entity) :
		Component(ecs::FoodGiverViewer), entity_(entity) {}

	void init() override;
	void draw() override;
};