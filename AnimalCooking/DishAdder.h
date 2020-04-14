#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>
class EntityManager;
class DishAdder
{
public:
	DishAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casilla);

private:
	void initializeComponent(const string& component, Entity* entity);
	EntityManager* em;
};

