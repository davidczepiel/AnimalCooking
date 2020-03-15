#include "InsertExpel.h"
#include <list>

InsertExpel::InsertExpel(Transport* tr) :
	Component(ecs::InsertExpel),
	transport_(tr),
	foodCooker_(nullptr)
{
}

InsertExpel::InsertExpel() :
	Component(ecs::InsertExpel),
	foodCooker_(nullptr),
	transport_(nullptr)
{
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
	foodCooker_ = GETCMP1_(FoodCooker);
}

void InsertExpel::insertFood(Cooker* c) {
	if (transport_.hasEmptyDish()) {
		if (c->getCookerState() == CookerStates::empty) {
			Dish* dish_ = static_cast<Dish*>(transport_.getObjectInHands());
			c->getFoods().insert(c->getFoods().end(), dish_->getFoodVector().begin(), dish_->getFoodVector().end());
			dish_->.getFoodVector().clear();
			foodCooker_->startCooked(c);
		}
	}
}

void InsertExpel::extractFood(Cooker *c){
	//if(transport_.hasEmptyDish() && c->getCookerState() != CookerStates::empty) <- Terminar de aclarar con el grupo si se puede sacar estando en cooking
	if (transport_.hasEmptyDish() && (c->getCookerState() == CookerStates::cooked ||
									  c->getCookerState() == CookerStates::burned)) {
		Dish* dish_ = static_cast<Dish*>(transport_.getObjectInHands());
		dish_->getFoodVector().insert(dish_->getFoodVector().end(), c->getFoods().begin(), c->getFoods().end());
		foodCooker_->clearFoods(c);
		c->setCookerState(CookerStates::empty);
	}
}