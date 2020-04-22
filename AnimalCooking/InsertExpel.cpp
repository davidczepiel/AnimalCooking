#include "InsertExpel.h"
#include "Dish.h"
#include <list>

//InsertExpel::InsertExpel() :
//	Component(ecs::InsertExpel),
//	foodCooker_(nullptr),
//	transport_(nullptr)
//{
//}

InsertExpel::InsertExpel(Transport* tr) :
	Component(ecs::InsertExpel),
	transport_(tr),
	foodCooker_(nullptr)
{
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
	foodCooker_ = GETCMP1_(FoodCooker);
}

void InsertExpel::insertFood(Cooker* cooker) {
	if (cooker->getCookerState() == CookerStates::empty &&
		transport_->getObjectTypeInHands() == Resources::Dish) {

			Dish* dish_ = static_cast<Dish*>(transport_->getObjectInHands());
			if (!dish_->getFoodVector().empty()) {
				for (auto& i : dish_->getFoodVector()) {
					i->setCanInteract(false);
				}
				cooker->getFoods().insert(cooker->getFoods().end(), dish_->getFoodVector().begin(), dish_->getFoodVector().end());
				dish_->getFoodVector().clear();
				foodCooker_->startCooked(cooker);
			}
	}
}

void InsertExpel::extractFood(Cooker *cooker, Timer* timer){
	if ((cooker->getCookerState() == CookerStates::cooked ||
		cooker->getCookerState() == CookerStates::burned) &&
		transport_->getObjectTypeInHands() == Resources::Dish) {

			Dish* dish_ = static_cast<Dish*>(transport_->getObjectInHands());
			dish_->getFoodVector().insert(dish_->getFoodVector().end(), cooker->getFoods().begin(), cooker->getFoods().end());
			for (auto& i : dish_->getFoodVector()) {
				i->setCanInteract(false);
			}
			cooker->getFoods().clear();
			cooker->setCookerState(CookerStates::empty);
			timer->timerReset();
	}
}