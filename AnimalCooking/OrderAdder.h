#pragma once
#include "jute.h"
#include "Entity.h"
#include <array>
#include <vector>
class Interactive;
class EntityManager;
class TimerViewer;
class OrderAdder
{
public:
	OrderAdder(EntityManager* mngr, jute::jValue& nivel, jute::jValue& general, std::array<Entity*, 2>& player, Entity* gameManager, const double casillaX, const double casillaY, TimerViewer* tv);
	std::vector<Interactive*>& getInteractives() { return interactives_; }

private:
	void switchPedido(const string& p, vector<Resources::FoodType>& pedido);
	void initializeComponent(const string& component, Entity* entity);
	std::vector<Interactive*> interactives_;
};

