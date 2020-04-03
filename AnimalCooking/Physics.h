#pragma once
#include "Component.h"
#include "CollisionsSystem.h"
class Physics :
	public Component
{
private:
	CollisionsSystem* colSystem;

public:
	Physics() :Component(ecs::Physics) {}
	bool Collided(SDL_Rect pos);
	void setCollisionSystem(CollisionsSystem* col) { colSystem=col; }
};

