#pragma once

#include "Manager.h"
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(Vector2D pos, Vector2D size, Texture* texture, double casilla, EntityManager* mn);
};

