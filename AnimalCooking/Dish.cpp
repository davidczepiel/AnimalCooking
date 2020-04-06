#include "Dish.h"

Dish::Dish(Vector2D pos_, Transport* transPlayer1, Transport* transPlayer2) : Pickable(transPlayer1, transPlayer2, nullptr),foods_(vector<Food*>())
{
}

// si el vector estaba vacío pone el iterador al principio
void Dish::addFood(Food* f)
{
	if (f != nullptr) 
	{
		foods_.push_back(f);				
		currentFood = foods_.begin();		
	}
}

Food* Dish::takeFood()
{
	//si el vector no se ha vaciado pone el iterador al principio para evitar errores
	if (!foods_.empty()) 
	{
		Food* aux = *currentFood;
		foods_.erase(currentFood);
		if (!foods_.empty())
			currentFood = foods_.begin();
		return aux;
	}
	else return nullptr;
}
//Comprobamos que no está el vector vacío y no se ha llegado al último elemento
void Dish::nextFood() 
{
	if (!foods_.empty() && currentFood != (--foods_.end()))
		currentFood++;
}
//Comprobamos que no está el vector vacío y no estamos en el primer elemento
void Dish::previousFood() 
{
	if (!foods_.empty() && currentFood != foods_.begin())
		currentFood--;
}



void Dish::clearFoods()
{	
	auto it = foods_.begin();
	while (it != foods_.end()) {
		delete* it;
		++it;
	}
	foods_.clear();
}
