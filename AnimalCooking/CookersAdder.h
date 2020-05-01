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
	CookersAdder(Entity* cookersPool, jute::jValue& jsonnivel, jute::jValue& jsongeneral, std::array<Entity*, 2> players, FoodPool* fp, const double casilla);
	void switchCookers(const string& cooker, int type, int n);
	void initializeComponent(const string& component, Entity* entity);
	list<Timer*>& getTimers() { return timers_; }
private:
	jute::jValue nivel;
	jute::jValue general;
	std::array<Entity*, 2>players;
	Entity* cookersPool;
	const double casillaLength;
	std::list<Timer*>timers_;
	template<typename T>
	void makeCooker(int type, int n);
};
