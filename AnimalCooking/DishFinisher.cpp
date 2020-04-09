#include "DishFinisher.h"
#include "FoodDictionary.h"

DishFinisher::DishFinisher(Transport* tr1, Transport* tr2):
	Component(ecs::DishFinisher), tr1_(tr1),tr2_(tr2)
{
}

DishFinisher::~DishFinisher()
{
}

void DishFinisher::finish()
{
	if ( tr1_->getObjectInHands() != nullptr && tr1_->getObjectTypeInHands() == Resources::PickableType::Dish) {
		Dish* dish = static_cast<Dish*>(tr1_->getObjectInHands());
		
		if (dish->getFoodVector().size() > 1) {
			Food* newFood = FoodDictionary::instance()->getResult(Resources::Cookers::Hands, dish->getFoodVector());
			dish->clearFoods();
			dish->getFoodVector().insert(dish->getFoodVector().begin(), newFood);
		}
	}
}