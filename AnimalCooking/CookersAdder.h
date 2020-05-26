#pragma once
#include "Entity.h"
#include "jute.h"
#include "FoodCooker.h"
#include "CookerViewer.h"
#include "InsertExpel.h"
#include "Cooker.h"
#include "SelectorPopUp.h"
#include<list>
class CookersAdder
{
public:
	CookersAdder(Entity* cookersPool, jute::jValue& jsonnivel, jute::jValue& jsongeneral, std::array<Entity*, 2> players, FoodPool* fp, const double casillaX, const double casillaY);
	void switchCookers(const string& cooker, int type, int n);
	void initializeComponent(const string& component, Entity* entity);
	list<Timer*>& getTimers() { return timers_; }

private:
	template<typename T>
	void makeCooker(int type, int n);

	Entity* cookersPool;
	std::array<Entity*, 2>players;	
	std::list<Timer*>timers_;
	jute::jValue nivel;
	jute::jValue general;

	const double casillaX;
	const double casillaY;
};
