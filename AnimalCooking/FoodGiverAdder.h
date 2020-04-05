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
	void SwitchFG(const string& fg,int type,int n);
	void initializeComponent(const string& component, Entity* entity);
	template <typename T>
	void makeFoodGiver(int type,int n);
	double casilla;
	jute::jValue nivel;
	jute::jValue general;
	EntityManager* mngr;
	Entity* gameManager;
	vector<Entity*>entities;
	std::array<Entity*, 2>players;

	
};

