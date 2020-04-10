#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"
#include "IngredientsPool.h"
#include "CookerPool.h"
#include "Collisions.h"
#include "Interactive.h"
#include <list>

class Ingredient;
class CollisionsSystem :
	public Component
{
public:
	CollisionsSystem() :Component(ecs::CollisionsSystem) { }

	void addCollider(Transform* t, bool isInmovable = true) { entidadesTr.push_back(std::make_pair(t, isInmovable)); }
	void addCollider(Interactive* i, bool isInmovable = false) { entidadesInt.push_back(std::make_pair(i, isInmovable)); }
	void addCollider(Ingredient* i, bool isInmovable = true) { entidadesIng.push_back(std::make_pair(i, isInmovable)); }
	void update();

private:
	list<std::pair<Transform*, bool>> entidadesTr;
	list<std::pair<Interactive*, bool>> entidadesInt;
	list<std::pair<Ingredient*, bool>> entidadesIng;

	list<SDL_Rect> collisions(SDL_Rect body);

	void checkCollision(SDL_Rect body, SDL_Rect other, list<SDL_Rect>& collisions);
	void resolveCollisions(Transform* tr);
	void resolveCollisions(Interactive* in);
	void resolveCollisions(Ingredient* in);

	void singleCollision(Transform* tr, const SDL_Rect& col);
	void verticalCollision(Transform* tr, const SDL_Rect& col);
	void horizontalCollision(Transform* tr, const SDL_Rect& col);
};

