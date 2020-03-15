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
	if (c->getCookerState() == CookerStates::empty) {
		c->setCookerState(CookerStates::cooking);
		c->getCookerTimer()->setTime(c->getCookingTime());
		c->getCookerTimer()->timerStart();
	}		
}

void FoodCooker::clearFoods(Cooker* c) {
	auto it = c->getFoods().begin();
	while (it != c->getFoods().end()) {
		delete *it;
		++it;
	}
	c->getFoods().clear();
}

void FoodCooker::update() {
	for (Cooker* c : pool_) {
		if (c->getCookerState() == CookerStates::cooking || c->getCookerState() == CookerStates::cooked) {
			if (!c->getCookerTimer()->isTimerEnd()) {
				c->getCookerTimer()->update();
			}
			else if (c->getCookerState() == CookerStates::cooking) {
				Food* newFood = FoodDictionary::instance()->getResult(c->getCookerType(), c->getFoods());				
				clearFoods(c);
				c->getFoods().push_back(newFood);

				c->setCookerState(CookerStates::cooked);
				c->getCookerTimer()->timerReset();
				c->getCookerTimer()->setTime(c->getCookingTime() / 2); //Tiempo de quemado a definir, de momento tQuemado = tCocinar/2
				c->getCookerTimer()->timerStart();
			}
			else {
				Food* burnedFood = FoodDictionary::instance()->getResult(c->getCookerType(), c->getFoods());
				clearFoods(c);
				c->getFoods().push_back(burnedFood);
				
				c->setCookerState(CookerStates::burned);
				c->getCookerTimer()->timerReset();
			}
		}
	}
}