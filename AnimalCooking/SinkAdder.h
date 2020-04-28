#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <string>
#include "SelectorPopUpEntity.h"
#include "InteractionRect.h"
class EntityManager;
class Interactive;
class SinkAdder
{
public:
	SinkAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casilla);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
private:
	void initializeComponent(const string& component, Entity* entity);
	std::vector<Interactive*> interactives_;
	EntityManager* em;
};
