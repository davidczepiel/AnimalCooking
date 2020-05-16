#pragma once
#include "Component.h"
class ButtonChangeOnClick : public Component
{
	enum State : size_t {
		False,
		True
	};
public:
	ButtonChangeOnClick(int s) : Component(ecs::ButtonChangeOnClick), state((State)s) {}
	void changeState() { state = State(1 - state); }
	inline const State& getState() const { return state; }
private:
	State state;
};

