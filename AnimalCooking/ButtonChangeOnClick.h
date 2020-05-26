#pragma once
#include "Component.h"
class ButtonChangeOnClick : public Component
{
	enum State : size_t {
		False,
		True
	};
public:
	ButtonChangeOnClick(int s) : Component(ecs::ButtonChangeOnClick), state_((State)s) {}
	void changeState() { state_ = State(1 - state_); }
	inline const State& getState() const { return state_; }

private:
	State state_;
};

