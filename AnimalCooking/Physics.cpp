#include "Physics.h"

bool Physics::Collided(SDL_Rect body, Vector2D vel)
{
	return colSystem->Collides(body, vel);
}


bool Physics::Collided(Transform* t, int Speed) {
	SDL_Rect body;
	body.x = t->getPos().getX()+ t->getVel().getX()*Speed;
	body.y = t->getPos().getY()+ t->getVel().getY()*Speed;
	body.w = t->getW();
	body.h = t->getH();
	if (colSystem->Collides(body, t->getVel())) {
		lastCol = colSystem->getLastCollision();
		return true;
	}
	else
		return false;
}

void Physics::ReadjustPos(Transform* t) {
	Vector2D finalPos;
	Vector2D pos = t->getPos();
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
	t->setPos(finalPos);
}

void Physics::ReadjustVel(Transform* t, int Speed) {
	Vector2D finalVel;
	Vector2D vel = t->getVel();
	if (lastCol.w > lastCol.h) {
		if (vel.getX() < 0)finalVel = Vector2D(-1, 0);
		else if(vel.getX()>0)finalVel = Vector2D(1, 0);
	}
	else {
		if (vel.getY() < 0)finalVel = Vector2D(0, -1);
		else if(vel.getY()>0)finalVel = Vector2D(0, 1);
	}
	t->setVel(finalVel);
	ReadjustPos(t);
	if (Collided(t,Speed))
		t->setVel(Vector2D(0,0));
}
