#include "InsertExpel.h"
#include "Dish.h"
#include <list>

//InsertExpel::InsertExpel() :
//	Component(ecs::InsertExpel),
//	foodCooker_(nullptr),
//	transport_(nullptr)
//{
//}

InsertExpel::InsertExpel(Transport* tr1, Transport* tr2) :
	Component(ecs::InsertExpel),
	transport1_(tr1), transport2_(tr2),
	foodCooker_(nullptr)
{
}

InsertExpel::~InsertExpel() {	
}

void InsertExpel::init() {
	foodCooker_ = GETCMP1_(FoodCooker);
}

void InsertExpel::insertFood(Cooker* cooker, int player) {

	Transport* t;
	if (player == 0) t = transport1_;
	else t = transport2_;

	if (cooker->getCookerState() == CookerStates::empty &&
		t->getObjectTypeInHands() == Resources::Dish) {

			Dish* dish_ = static_cast<Dish*>(t->getObjectInHands());
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

void InsertExpel::extractFood(Cooker *cooker, Timer* timer, int player){

	Transport* t;
	if (player == 0) t = transport1_;
	else t = transport2_;

	if ((cooker->getCookerState() == CookerStates::cooked ||
		cooker->getCookerState() == CookerStates::burned) &&
		t->getObjectTypeInHands() == Resources::Dish) {

			Dish* dish_ = static_cast<Dish*>(t->getObjectInHands());
			dish_->getFoodVector().insert(dish_->getFoodVector().end(), cooker->getFoods().begin(), cooker->getFoods().end());
			for (auto& i : dish_->getFoodVector()) {
				i->setCanInteract(false);
			}
			cooker->getFoods().clear();
			cooker->setCookerState(CookerStates::empty);
			timer->timerReset();
	}
}