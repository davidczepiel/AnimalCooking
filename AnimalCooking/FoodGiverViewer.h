#pragma once

#include "Component.h"
#include "FoodGiver.h"

class FoodGiverViewer : public Component
{
public:
	FoodGiverViewer(FoodGiver* entity);

	void init() override;
	void draw() override;
private:
	FoodGiver* entity_;
	Texture* texture_;
	SDL_Rect rect_;
};