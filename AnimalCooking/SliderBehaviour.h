#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SliderBehaviour : public Component
{
private:
	bool active;
protected:
	Transform* transform;
	SDL_Rect rectMovePoint;
	float value;

public:
	SliderBehaviour() : Component(ecs::SliderBehaviour), transform(nullptr), active(false), value(0.5) {}

	void init() override;
	void update() override;

	inline SDL_Rect* getMovePointRect() { return &rectMovePoint; }
	inline float getValue() { return value; }
};

