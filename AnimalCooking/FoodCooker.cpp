#include "FoodCooker.h"
#include "FoodDictionary.h"

FoodCooker::FoodCooker() :
	Component(ecs::FoodCooker){
}

FoodCooker::~FoodCooker() {
}

void FoodCooker::init() {
	pool_ = GETCMP1_(CookerPool)->getPool();
}

void FoodCooker::startCooked(Cooker *c) {
	if (c->getCookerState() == CookerStates::ready) {
		c->setCookerState(CookerStates::cooking);
		c->getCookerTimer()->setTime(c->getCookingTime());
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
				//Food* newFood = FoodDictionary::instance()->getResult(c->getCookerType(), c->getFoods());
				c->setCookerState(CookerStates::cooked);
				c->getCookerTimer()->timerReset();
				c->getCookerTimer()->setTime(c->getCookingTime() / 2); //Tiempo de quemado a definir, de momento tQuemado = tCocinar/2
				//c->setTexture();
			}
		}
		else if (c->getCookerState() == CookerStates::cooked && c->getCookerTimer()->isTimerEnd()) {
			c->setCookerState(CookerStates::burned);
			c->getCookerTimer()->timerReset();
			//c->setTexture();
		}
	}
}