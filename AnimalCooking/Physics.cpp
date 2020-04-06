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

Vector2D Physics::ReadjustPos(Vector2D pos) {
	Vector2D finalPos;
	if (lastCol.w > lastCol.h) {
		int diference = abs(pos.getY() - lastCol.y);
		if (lastCol.y > pos.getY())
			finalPos =(Vector2D(pos.getX(),pos.getY() - lastCol.h));
		else
			finalPos =(Vector2D(pos.getX(), pos.getY() + lastCol.h));
	}
	else {
		int diference = abs(pos.getX() - lastCol.x);
		if (lastCol.x > pos.getX())
			finalPos =(Vector2D(pos.getX() - lastCol.w, pos.getY()));
		else
			finalPos=(Vector2D(pos.getX() + lastCol.w, pos.getY()));
	}
	return finalPos;
}

Vector2D Physics::ReadjustVel(Vector2D vel) {
	Vector2D finalVel;
	if (lastCol.w > lastCol.h) {
		if (vel.getX() < 0)finalVel = Vector2D(-1, 0);
		else if(vel.getX()>0)finalVel = Vector2D(1, 0);
	}
	else {
		if (vel.getY() < 0)finalVel = Vector2D(0, -1);
		else if(vel.getY()>0)finalVel = Vector2D(0, 1);
	}

	return finalVel;
}
