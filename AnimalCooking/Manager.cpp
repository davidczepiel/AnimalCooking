#include "Manager.h"

EntityManager::EntityManager(SDLGame* game) :
	game_(game) {
}

EntityManager::~EntityManager() {
}

void EntityManager::update() {
	for (auto &e : entities) {
		e->update();
	}
}

void EntityManager::draw() {
	for (int i = 0; i < ecs::maxGroups; ++i) {
		for (auto& e : entitiesGroup[i]) {
			e->draw();
		}
	}
}

Entity* EntityManager::addEntity() {
	Entity* e = new Entity(game_,this);
	std::unique_ptr<Entity> uPtr( e );
	entities.emplace_back(std::move(uPtr));
	return e;
}

void EntityManager::addEntity(Entity* e)
{
	entities.emplace_back(e);
}

void EntityManager::addToGroup(Entity* e, ecs::GroupID id) {
	entitiesGroup[id].push_back(e);
}
