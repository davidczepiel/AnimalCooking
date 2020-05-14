#pragma once
#include "Component.h"
#include "Timer.h"

class Animator : public Component	
{
	
public:

	enum States { Idle, IdleWithKnife, IdleWithMace, IdleWithGrater, IdleWithNet,IdleWithDishFood, IdleWithDirtyKnife, IdleWithDirtyMace, IdleWithDirtyGrater, IdleWithDirtyNet,
		          Walk, WalkWithKnife, WalkWithMace, WalkWithGrater, WalkWithNet,WalkWithDishFood, WalkWithDirtyKnife, WalkWithDirtyMace, WalkWithDirtyGrater, WalkWithDirtyNet,
		          AttackWithKnife, AttackWithMace, AttackWithGrater, AttackWithNet };
	
	
	Animator();
	~Animator() { }

	States getCurrentState() { return currentState; };
	void setCurrentState(States s) { currentState = s; };

	DefaultTimer getTimer() { return dt; }

	void setDir(Vector2D v) { dir = v; }
	Vector2D getDir() { return dir; }

private:

	States currentState;
	DefaultTimer dt;
	Vector2D dir;
};

