#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SliderBehaviour : public Component
{
protected:
	Transform* transform;
	SDL_Rect rectMovePoint;
	int value;

public:
	SliderBehaviour() : Component(ecs::SliderBehaviour), transform(nullptr) {}

	void init() override;
	void update() override;

	inline const SDL_Rect* getMovePointRect() { return &rectMovePoint; }
};

