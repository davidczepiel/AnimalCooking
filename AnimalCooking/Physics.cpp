#include "Physics.h"

bool Physics::Collided(SDL_Rect body, Vector2D vel)
{
	return colSystem->Collides(body, vel);
}


bool Physics::Collided(Transform* t) {
	SDL_Rect body;
	body.x = t->getPos().getX();
	body.y = t->getPos().getY();
	body.w = t->getW();
	body.h = t->getH();
	if (colSystem->Collides(body, t->getVel())) {
		lastCol = colSystem->getLastCollision();
		return true;
	}
	else
		return false;
}
