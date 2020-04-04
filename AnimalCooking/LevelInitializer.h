#pragma once
#include "jute.h"
#include "Resources.h"
#include <array>

class EntityManager;
class Entity;
class LevelInitializer
{
public:
	LevelInitializer(EntityManager* em, Resources::Level level);
	void initializeComponent(const string& component, Entity* entity);
private:

	void initialize_players();
	void initialize_ingredientsPool();
	void initialize_foodPool();

	std::array<Entity*, 2> players;
	Entity* ingPoolEntity_;

	EntityManager* emPlaystate;
	jute::jValue jsonLevel;
	jute::jValue jsonGeneral;
};

