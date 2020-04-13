#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>
class EntityManager;
class Interactive;
class DishAdder
{
public:
	DishAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casilla);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
private:
	void initializeComponent(const string& component, Entity* entity);
	EntityManager* em;
	std::vector<Interactive*> interactives_;
};

