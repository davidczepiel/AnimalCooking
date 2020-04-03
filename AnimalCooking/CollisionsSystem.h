#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"
#include "IngredientsPool.h"
#include "CookerPool.h"
#include "Collisions.h"
#include "Interactive.h"

class CollisionsSystem :
	public Component
{

public:
	CollisionsSystem() :Component(ecs::CollisionsSystem) {}
	bool Collides(SDL_Rect body);
	void addCollider(Transform* t) { entidades.push_back(t);}
	void addCollider(Interactive* i) { entidadesInt.push_back(i); }

	vector<Transform*> entidades;
	vector<Interactive*> entidadesInt;
	vector<Interactive*> ingredientesPools;
	vector<Interactive*> cookersPool;


};

