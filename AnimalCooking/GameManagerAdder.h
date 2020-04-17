#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>

class EntityManager;
class UtensilsPool;
class FoodPool;
class IngredientsPool;
class CollisionsSystem;

class GameManagerAdder
{
public:
	GameManagerAdder(Entity* gameManager,EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, UtensilsPool* pool_, FoodPool* fp, IngredientsPool* ip, Resources::Level level);
	
private:
	void initializeComponent(const string& component, Entity* entity);
	void initializeCollisionSystem(CollisionsSystem* gameManager, std::array<Entity*, 2>& player, IngredientsPool* ip);
};

