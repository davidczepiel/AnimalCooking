#pragma once
#include "Component.h"

class Animator : public Component	
{
	
public:

	enum State {Idle, Walk, Attack};
	
	Animator();
	~Animator() { }

	void update()override;

	State getCurrentState() { return currentState; };
	void setCurrentState(State s) { currentState = s; };
private:

	State currentState;
	int animSpeed;
};

