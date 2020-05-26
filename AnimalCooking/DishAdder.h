#pragma once
#include "jute.h"
#include "Entity.h"
#include "FoodPool.h"
#include "DishPool.h"
#include <array>
#include <string>
class EntityManager;
class Interactive;
class DishAdder
{
public:
	DishAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, FoodPool* fp, const double casillaX, const double casillaY);
	~DishAdder() {}

	std::vector<Interactive*>& getInteractives() { return interactives_; }
	DishPool* getDishPool() { return dp; }
private:
	void initializeComponent(const string& component, Entity* entity);

	EntityManager* em;
	std::vector<Interactive*> interactives_;
	DishPool* dp;
};

