#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"
#include "IngredientsPool.h"
#include "CookerPool.h"
#include "Collisions.h"
#include "Interactive.h"
#include <list>

class CollisionsSystem :
	public Component
{
	SDL_Rect lastCol;

public:
	CollisionsSystem() :Component(ecs::CollisionsSystem) { }
	bool Collides(SDL_Rect body, Vector2D vel);
	void addCollider(Transform* t) { entidades.push_back(t);}
	void addCollider(Interactive* i) { entidadesInt.push_back(i); }
	SDL_Rect getLastCollision();

	list<Transform*> entidades;
	list<Interactive*> entidadesInt;
	list<Interactive*> ingredientesPools;
	list<Interactive*> cookersPool;


};

