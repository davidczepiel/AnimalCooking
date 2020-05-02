#pragma once
#include "Component.h"
#include "Timer.h"

class Animator : public Component	
{
	
public:

	enum States { Idle, IdleWithKnife, IdleWithMace, IdleWithGrater, IdleWithNet,IdleWithDish,
		          Walk, WalkWithKnife, WalkWithMace, WalkWithGrater, WalkWithNet,WalkWithDish,
		          AttackWithKnife, AttackWithMace, AttackWithGrater, AttackWithNet };
	
	
	Animator();
	~Animator() { }

	States getCurrentState() { return currentState; };
	void setCurrentState(States s) { currentState = s; };

	DefaultTimer getTimer() { return dt; }

private:

	States currentState;
	SDL_Rect clip;
	DefaultTimer dt;
};

