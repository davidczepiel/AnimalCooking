#pragma once
#include "jute.h"
#include "Entity.h"
#include "FoodGiver.h"
#include "FoodGiverViewer.h"
#include "SelectorPopUpEntity.h"
class FoodGiverAdder
{
public:
	FoodGiverAdder(EntityManager*mngr, jute::jValue nivel, jute::jValue general, std::array<Entity*, 2>& player,Entity* gameManager,const double casilla);
private:
	FoodGiver* SwitchFG(const string& fg,int type,int n);

	template <typename T>
	FoodGiver* makeFoodGiver(int type,int n);

	void initializeComponent(const string& component, Entity* entity);

	double casilla;
	jute::jValue nivel;
	jute::jValue general;
	EntityManager* mngr;
	Entity* gameManager;
	std::array<Entity*, 2>players;
};

