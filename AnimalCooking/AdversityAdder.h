#pragma once
#include "Manager.h"

class GhostPool;
class AdversityAdder
{
public:
	AdversityAdder(jute::jValue& nivel, EntityManager* mngr, std::array<Entity*, 2>& players, 
		Entity* cookersPool, Entity* ingredientsPool, Entity* utensilsPool, Entity* firespool, GhostPool* ghostPool);
};

