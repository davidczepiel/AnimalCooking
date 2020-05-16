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
	CollisionsSystem(const double casillaX, const double casillaY, const size_t leftBorder) :Component(ecs::CollisionsSystem), flexibilityX(casillaX/20),flexibilityY(casillaY/20), leftBorder(leftBorder)  { }

	void addCollider(Transform* t, bool isMovable = true) { entidadesTr.push_back(std::make_pair(t, isMovable)); }
	void addCollider(Interactive* i) { entidadesInt.push_back(std::make_pair(i, false)); }
	void addCollider(Ingredient* i) { entidadesIng.push_back(std::make_pair(i, true)); }
	void removeCollider(Ingredient* i) { entidadesIng.remove(std::make_pair(i, true)); }
	void update();

private:

	int flexibilityX;
	int flexibilityY;

	size_t leftBorder;

	list<std::pair<Transform*, bool>> entidadesTr;
	list<std::pair<Interactive*, bool>> entidadesInt;
	list<std::pair<Ingredient*, bool>> entidadesIng;

	list<SDL_Rect> collisions(SDL_Rect body);

	void changeBackCol(std::list<SDL_Rect>& collisions, const SDL_Rect& col);

	bool checkCollision(const SDL_Rect& body, const SDL_Rect& other, list<SDL_Rect>& collisions);
	ColisionType resolveCollisions(Vector2D& pos, const Vector2D& offset, const Vector2D& size, const Vector2D& vel, const bool imIng = false);
	ColisionType worldCollision(Vector2D& pos, const Vector2D& offset, const Vector2D& size, const Vector2D& vel, const bool imIng);

	ColisionType singleCollision(Vector2D& pos, const Vector2D& offset, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);
	void verticalCollision(Vector2D& pos, const Vector2D& offset, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);
	void horizontalCollision(Vector2D& pos, const Vector2D& offset, const Vector2D& size, const Vector2D& vel, const SDL_Rect& col);

	void tellIngredient(Ingredient* en, const ColisionType& colType);
};

