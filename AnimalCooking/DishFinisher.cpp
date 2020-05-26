#include "DishFinisher.h"
#include "FoodDictionary.h"

DishFinisher::DishFinisher(Transport* tr1, Transport* tr2) :
	Component(ecs::DishFinisher), tr1_(tr1), tr2_(tr2)
{
}

DishFinisher::~DishFinisher()
{
}

void DishFinisher::finish(int id, Dish* d)
{
	Transport* player = nullptr;
	//Dependiendo del numero que me ha llegado trabajare con el player1 o el player2
	if (id == 0) player = tr1_;
	else player = tr2_;

	if (d->getFoodVector().size() > 1) {
		Food* newFood = FoodDictionary::instance()->getResult(Resources::Cookers::Hands, d->getFoodVector());
		d->clearFoods();
		d->addFinalFood(newFood);
	}	
}