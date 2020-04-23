#pragma once
#include "jute.h"
#include "Vector2D.h";
#include "Resources.h"

class Wall;
class CollisionsSystem;
class EntityManager;
#include <array>
#include "Transform.h"

struct Data {
	Data(Vector2D pos, Vector2D size, Resources::TextureId t) : pos(pos), size(size), t(t) {}
	Vector2D pos;
	Vector2D size;
	Resources::TextureId t;
};

class WallAdder
{
public:
	WallAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, std::array<Entity*, 2>& players, const double casilla, const double offset);
private:
	void maker(const Data& d, const double casilla, CollisionsSystem* colSys_, EntityManager* mngr);
};

