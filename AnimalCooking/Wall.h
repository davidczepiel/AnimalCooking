#pragma once

#include "Manager.h"
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(Vector2D pos, Vector2D size, double rot, Texture* texture, double casilla, EntityManager* mn);
};

