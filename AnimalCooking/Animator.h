#pragma once
#include "Component.h"
#include "Timer.h"

class Animator : public Component	
{
	
public:
	enum States { Idle, IdleWithKnife, IdleWithMace, IdleWithGrater, IdleWithNet,IdleWithDishFood, IdleWithDirtyKnife, IdleWithDirtyMace, IdleWithDirtyGrater, IdleWithDirtyNet,IdleWithFillCube,IdleWithEmptyCube,
		          Walk, WalkWithKnife, WalkWithMace, WalkWithGrater, WalkWithNet,WalkWithDishFood, WalkWithDirtyKnife, WalkWithDirtyMace, WalkWithDirtyGrater, WalkWithDirtyNet,WalkWithFillCube,WalkWithEmptyCube,
		          AttackWithKnife, AttackWithMace, AttackWithGrater, AttackWithNet,UseCube };	
	
	Animator();
	~Animator() { }

	
	void setCurrentState(States s) { currentState = s; };
	void setDir(Vector2D v) { dir = v; }
	DefaultTimer getTimer() { return dt; }
	States getCurrentState() { return currentState; };	
	Vector2D getDir() { return dir; }

private:
	States currentState;
	DefaultTimer dt;
	Vector2D dir;
};

