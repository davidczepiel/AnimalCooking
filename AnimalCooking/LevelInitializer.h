#pragma once
#include "jute.h"
#include "Resources.h"
#include <array>

class EntityManager;
class Entity;
class ScreenLoader;
class LevelInitializer
{
public:
	LevelInitializer(EntityManager* em, Resources::Level level, ScreenLoader* sL);
private:

	void initialize_players();
	void initialize_ingredientsPool();
	void initialize_foodPool();
	void initialize_utensilPool();

	std::array<Entity*, 2> players;
	Entity* ingPoolEntity_;

	ScreenLoader* sL;

	EntityManager* emPlaystate;
	jute::jValue jsonLevel;
	jute::jValue jsonGeneral;
};

