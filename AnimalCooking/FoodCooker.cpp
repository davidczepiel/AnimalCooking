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
	if (c->getCookerState() == CookerStates::full) {
		c->setCookerState(CookerStates::cooking);
		c->getCookerTimer()->timerStart();
	}		
}

void FoodCooker::update() {
	for (Cooker* c : pool_) {
		if (c->getCookerState() == CookerStates::cooking){

			if (!c->getCookerTimer()->isTimerEnd()) {
				c->getCookerTimer()->update();
			}
			else {
				c->setCookerState(CookerStates::cooked);
				c->getCookerTimer()->timerReset();
				//c->setTexture();
			}
		}
	}
}