#pragma once
#include "Entity.h"
#include "Transform.h"
#include "DoorRenderer.h"
#include <array>

class Door : public Entity
{
public:
	Door(Vector2D pos, Vector2D size, Texture* texture, Transform* p1, Transform* p2, EntityManager* em) : Entity(SDLGame::instance(), em) {
		Transform* tr = addComponent<Transform>(pos, Vector2D(), size.getX(), size.getY());
		addComponent<DoorRenderer>(tr, p1, p2, texture);
	}
	~Door() {}
};

