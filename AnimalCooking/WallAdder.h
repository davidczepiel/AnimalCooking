#pragma once
#include "jute.h"
#include "Vector2D.h"
#include "Resources.h"
#include <array>
#include "Transform.h"
class Wall;
class CollisionsSystem;
class EntityManager;

struct Data {
	Data(Vector2D pos, Vector2D size, Resources::TextureId t) : pos(pos), size(size), t(t) {}
	Vector2D pos;
	Vector2D size;
	Resources::TextureId t;
};

class WallAdder
{
public:
	WallAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, std::array<Entity*, 2>& players, const double casillaX, const double casillaY, const double offsetX, const double offsetY);
	~WallAdder() {}
private:
	void maker(const Data& d, const double casillaX, const double casillaY, CollisionsSystem* colSys_, EntityManager* mngr, const double offsetX, const double offsetY, ecs::GroupID id = ecs::GroupID::Layer2);
};

