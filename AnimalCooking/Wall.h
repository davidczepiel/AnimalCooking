#pragma once

#include "Manager.h"
#include "Entity.h"
#include "IngredientsPool.h"
class Wall : public Entity
{
public:
	Wall(Vector2D pos, Vector2D size, Texture* texture, double casillaX, const double casillaY, double thickness, EntityManager* mn);
	~Wall() {}
};

