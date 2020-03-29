#pragma once

#include "SDLGame.h"
#include "Entity.h"

class Entity;

class EntityManager {
public:
	EntityManager(SDLGame* game);
	virtual ~EntityManager();

	
	void update();
	void draw();
	Entity* addEntity();
	void addEntity(Entity* e);
	void addToGroup(Entity* e, ecs::GroupID id);

private:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<vector<Entity*>, ecs::maxGroups> entitiesGroup;
};
