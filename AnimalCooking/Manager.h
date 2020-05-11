#pragma once

#include "SDLGame.h"
#include "Entity.h"
#include <list>

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
	std::array<std::list<Entity*>, ecs::maxGroups>& getGroups() { return entitiesGroup; }

private:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::list<Entity*>, ecs::maxGroups> entitiesGroup;
};
