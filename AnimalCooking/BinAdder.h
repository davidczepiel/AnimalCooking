#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>
class EntityManager;
class Interactive;
class BinAdder
{
public:
	BinAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casillaX, const double casillaY);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
private:
	void initializeComponent(const string& component, Entity* entity);
	std::vector<Interactive*> interactives_;
	EntityManager* em;
};

