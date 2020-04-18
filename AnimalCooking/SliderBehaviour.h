#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SliderBehaviour : public Component
{
protected:
	Texture* sliderBackground;
	Texture* sliderMovePoint;
	Transform* transform;
	SDL_Rect rectMovePoint;

public:
	SliderBehaviour() : Component(ecs::SliderBehaviour), sliderBackground(nullptr), sliderMovePoint(nullptr), transform(nullptr) {}

	void init();
	void update();
};

