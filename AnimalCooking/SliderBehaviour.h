#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class SliderBehaviour : public Component
{
public:
	SliderBehaviour() : Component(ecs::SliderBehaviour), transform(nullptr), active(false), focused(false), value(0.5), padNavEnable(false) {}

	void init() override;
	void update() override;

	inline SDL_Rect* getMovePointRect() { return &rectMovePoint; }
	inline float getValue() { return value; }

	inline void move(int value) { rectMovePoint.x += value; }
	void movePercentage(float value);

	inline void setPadNavEnable(const bool& b) { padNavEnable = b; }
	inline bool getPadEnable() const { return padNavEnable; }

	inline void setFocused(const bool& b) { focused = b; }
	inline bool getFocused() const { return focused; }
	inline bool getActive() const { return active; }
protected:
	Transform* transform;
	SDL_Rect rectMovePoint;
	float value;
private:
	bool active;
	bool focused;
	bool padNavEnable;
};

