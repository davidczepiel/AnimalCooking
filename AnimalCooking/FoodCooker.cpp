#include "FoodCooker.h"

FoodCooker::FoodCooker() :
	Component(ecs::FoodCooker){
}

FoodCooker::~FoodCooker() {
}

void FoodCooker::init() {
	pool_ = GETCMP1_(CookerPool)->getPool();
}

void FoodCooker::startCooked(Cooker *c) {
	c->setCookerState(CookerStates::cooking);
}

void FoodCooker::update() {
	for (Cooker* c : pool_) {
		if (c->getCookerState == CookerStates::cooking) {

		}
	}
}