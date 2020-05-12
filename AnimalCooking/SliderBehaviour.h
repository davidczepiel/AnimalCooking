#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SliderBehaviour : public Component
{
public:
	SliderBehaviour() : Component(ecs::SliderBehaviour), transform(nullptr), active(false), value(0.5), padNavEnable(false) {}

	void init() override;
	void update() override;

	inline SDL_Rect* getMovePointRect() { return &rectMovePoint; }
	inline float getValue() { return value; }

	inline void move(int value) { rectMovePoint.x += value; }
	inline void setPadNavEnable(const bool& b) { padNavEnable = b; }
protected:
	Transform* transform;
	SDL_Rect rectMovePoint;
	float value;
private:
	bool active;
	bool padNavEnable;
};

