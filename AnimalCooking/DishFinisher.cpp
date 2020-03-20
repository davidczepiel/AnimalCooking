#include "DishFinisher.h"
#include "FoodDictionary.h"

DishFinisher::DishFinisher(Transport* tr):
	Component(ecs::DishFinisher), tr_(tr)
{
}

DishFinisher::~DishFinisher()
{
}

void DishFinisher::finish()
{
	if (tr_->getObjectTypeInHands() == Resources::PickableType::Dish) {
		Dish* dish = static_cast<Dish*>(tr_->getObjectInHands());
		
		if (dish->getFoodVector().size() > 1) {
			Food* newFood = FoodDictionary::instance()->getResult(Resources::Cookers::Hands, dish->getFoodVector());
			dish->clearFoods();
			dish->getFoodVector().insert(dish->getFoodVector().begin(), newFood);
		}
	}
}