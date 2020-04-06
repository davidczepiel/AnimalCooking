#pragma once
#include "Component.h"
#include "CollisionsSystem.h"
#include "Transform.h"
class Physics :
	public Component
{
private:
	CollisionsSystem* colSystem;
	SDL_Rect lastCol;
	void ReadjustPos(Transform* t);

public:
	Physics() :Component(ecs::Physics) {}
	bool Collided(SDL_Rect pos, Vector2D vel);
	bool Collided(Transform* t, int Speed);
	void setCollisionSystem(CollisionsSystem* col) { colSystem=col; }
	SDL_Rect getLastCol() { return lastCol; }
	void ReadjustVel(Transform* t, int Speed);
};

