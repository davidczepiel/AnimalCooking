#pragma once
#include "Entity.h"
#include "jute.h"
#include "FoodCooker.h"
#include "CookerViewer.h"
#include "InsertExpel.h"
#include "Cooker.h"
class CookersAdder
{
public:
	CookersAdder(Entity* cookersPool, jute::jValue& jsonnivel, jute::jValue& jsongeneral, std::array<Entity*, 2> players, FoodPool* fp);
	void switchCookers(const string& cooker, int type, int n);
	void initializeComponent(const string& component, Entity* entity);
private:
	jute::jValue nivel;
	jute::jValue general;
	std::array<Entity*, 2>players;
	Entity* cookersPool;
	template<typename T>
	void makeCooker(int type, int n);
};

