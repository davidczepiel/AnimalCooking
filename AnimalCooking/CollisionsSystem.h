#pragma once
#include "Component.h"
#include <list>

class Ingredient;
class Interactive;
class Transform;

enum ColisionType : size_t {
	noColision,
	horizontal,
	vertical,
	both
};

class CollisionsSystem :
	public Component
{
public:
	CollisionsSystem() :Component(ecs::CollisionsSystem) { }

	void addCollider(Transform* t, bool isMovable = true) { entidadesTr.push_back(std::make_pair(t, isMovable)); }
	void addCollider(Interactive* i) { entidadesInt.push_back(std::make_pair(i, false)); }
	void addCollider(Ingredient* i, bool isMovable = true) { entidadesIng.push_back(std::make_pair(i, isMovable)); }
	void removeCollider(Ingredient* i) { entidadesIng.remove(std::make_pair(i, true)); }
	void update();

private:

	int flexibility = 10;

	list<std::pair<Transform*, bool>> entidadesTr;
	list<std::pair<Interactive*, bool>> entidadesInt;
	list<std::pair<Ingredient*, bool>> entidadesIng;

	list<SDL_Rect> collisions(SDL_Rect body);

	void changeBackCol(std::list<SDL_Rect>& collisions, const SDL_Rect& col);

	bool checkCollision(const SDL_Rect& body, const SDL_Rect& other, list<SDL_Rect>& collisions);
	ColisionType resolveCollisions(Vector2D& pos, const Vector2D& size, const Vector2D& vel);

	ColisionType singleCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);
	void verticalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);
	void horizontalCollision(Vector2D& pos, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);

	void tellIngredient(Ingredient* en, const ColisionType& colType);
};

