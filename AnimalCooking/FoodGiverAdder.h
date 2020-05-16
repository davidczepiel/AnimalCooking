#pragma once
#include "jute.h"
#include "Entity.h"
#include "FoodGiver.h"
#include "FoodGiverViewer.h"
#include "SelectorPopUpEntity.h"
class FoodGiverAdder
{
public:
	FoodGiverAdder(EntityManager* mngr, jute::jValue nivel, jute::jValue general, std::array<Entity*, 2>& player, Entity* gameManager, const double casillaX, const double casillaY);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
private:
	FoodGiver* SwitchFG(const string& fg, int type, int n);

	template <typename T>
	FoodGiver* makeFoodGiver(int type, int n);

	void initializeComponent(const string& component, Entity* entity);

	double casillaX;
	double casillaY;
	jute::jValue nivel;
	jute::jValue general;
	EntityManager* mngr;
	Entity* gameManager;
	std::array<Entity*, 2>players;
	std::vector<Interactive*> interactives_;
};

