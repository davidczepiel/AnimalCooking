#pragma once
#include "jute.h"

class Wall;
class CollisionsSystem;
class EntityManager;

class WallAdder
{
public:
	WallAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, CollisionsSystem* colSys_, const double casilla, const double offset);
};

