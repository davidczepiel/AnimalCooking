#include "CollisionsSystem.h"



bool CollisionsSystem::Collides(SDL_Rect b) {
	bool hasCollided = false;
	int i = 0;
	Vector2D body = Vector2D(b.x, b.y);
	while ( !hasCollided && i<entidades.size()) {
		if (Collisions::collides(body, b.w, b.h,
			entidades.at(i)->getPos(),entidades.at(i)->getW(),entidades.at(i)->getH()))
			hasCollided = true;
		i++;
	}
	i = 0;
	while (!hasCollided && i < entidadesInt.size()) {
		if (Collisions::collides(body, b.w, b.h,
			entidadesInt.at(i)->getPos(), entidadesInt.at(i)->getSize().getX(), entidadesInt.at(i)->getSize().getY()))
			hasCollided = true;
		i++;
	}
	i = 0;
	while (!hasCollided && i < cookersPool.size()) {
		if (Collisions::collides(body, b.w, b.h,
			cookersPool.at(i)->getPos(), cookersPool.at(i)->getSize().getX(), cookersPool.at(i)->getSize().getY()))
			hasCollided = true;
		i++;
	}
	i = 0;
	while (!hasCollided && i < ingredientesPools.size()) {
		if (Collisions::collides(body, b.w, b.h,
			ingredientesPools.at(i)->getPos(), cookersPool.at(i)->getSize().getX(), cookersPool.at(i)->getSize().getY()))
			hasCollided = true;
		i++;
	}

	return hasCollided;
}