#include "FoodCooker.h"
#include "FoodDictionary.h"

FoodCooker::FoodCooker(FoodPool* fp) :
	Component(ecs::FoodCooker), fp_(fp){
}

FoodCooker::~FoodCooker() {
}

void FoodCooker::init() {
	pool_ = GETCMP1_(CookerPool);
}

void FoodCooker::startCooked(Cooker *c) {
	if (c->getCookerState() == CookerStates::empty) {
		c->setCookerState(CookerStates::cooking);
		c->getCookerTimer()->setTime(c->getCookingTime());
		c->getCookerTimer()->timerStart();
	}		
}

void FoodCooker::clearFoods(Cooker* c) {
	for (auto& it : c->getFoods()) {
		it->Destroy();
	}
	c->getFoods().clear();
}

void FoodCooker::update() {
	for (auto& c : pool_->getPool()) {
		if (c->getCookerState() == CookerStates::cooking || c->getCookerState() == CookerStates::cooked) {
			c->sound();
			if (!c->getCookerTimer()->isTimerEnd()) {
				c->getCookerTimer()->update();
			}
			else if (c->getCookerState() == CookerStates::cooking) {
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::CookedFood, 0);
				Food* newFood = FoodDictionary::instance()->getResult(c->getCookerType(), c->getFoods());	
				newFood->setCanInteract(false);
				clearFoods(c);
				fp_->AddFood(newFood);
				c->getFoods().push_back(newFood);

				c->setCookerState(CookerStates::cooked);
				c->getCookerTimer()->timerReset();
				c->getCookerTimer()->setTime(c->getCookingTime() / 2); //Tiempo de quemado a definir, de momento tQuemado = tCocinar/2
				c->getCookerTimer()->timerStart();
			}
			else {
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::BurnedBeep,0);
				Food* burnedFood = FoodDictionary::instance()->getResult(c->getCookerType(), c->getFoods());
				burnedFood->setCanInteract(false);
				clearFoods(c);
				fp_->AddFood(burnedFood);
				c->getFoods().push_back(burnedFood);
				
				c->setCookerState(CookerStates::burned);
				c->getCookerTimer()->timerReset();
			}
		}
	}
}