#pragma once
#include "Component.h"

class Animator : public Component	
{
	
public:

	enum States { Idle, IdleWithKnife, IdleWithMace, IdleWithGrater, IdleWithNet,
		          Walk, WalkWithKnife, WalkWithMace, WalkWithGrater, WalkWithNet,
		          Attack, AttackWithKnife, AttackWithMace, AttackWithGrater, AttackWithNet };
	
	
	Animator();
	~Animator() { }

	States getCurrentState() { return currentState; };
	void setCurrentState(States s) { currentState = s; };
	void setDir(Vector2D v) { dir = v; }
	Vector2D getDir() { return dir; }
	DefaultTimer getTimer() { return dt; }

private:

	States currentState;
	DefaultTimer dt;
	Vector2D dir;
};

