#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>
class EntityManager;
class BinAdder
{
public:
	BinAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player);

private:
	void initializeComponent(const string& component, Entity* entity);
	EntityManager* em;
};

