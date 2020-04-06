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

public:
	Physics() :Component(ecs::Physics) {}
	bool Collided(SDL_Rect pos, Vector2D vel);
	bool Collided(Transform* t);
	void setCollisionSystem(CollisionsSystem* col) { colSystem=col; }
	SDL_Rect getLastCol() { return lastCol; }
	Vector2D ReadjustPos(Vector2D pos);
	Vector2D ReadjustVel(Vector2D vel);
};

