#include "Dish.h"

Dish::Dish() 
{

}




// si la lista estaba vacía pone el iterador al principio
void Dish::addFood(Food* f)
{
	if (f != nullptr) {
		foods_.push_back(f);
		if (foods_.size() == 1)
		{
			currentFood = foods_.begin();
		}
	}

}

Food* Dish::takeFood()
{//si la lista no se ha vaciado pone el iterador al principio para evitar errores
	if (!foods_.empty()) {
		Food* aux = *currentFood;
		foods_.remove(*currentFood);
		if (!foods_.empty())
			currentFood = foods_.begin();
		return aux;
	}
	else return nullptr;
}
//Comprobamos que no está la lista vacía y no se ha llegado al último elemento
void Dish::nextFood() {
	if (!foods_.empty() && currentFood != (--foods_.end()))
		currentFood++;
}
//Comprobamos que no está la lista vacía y no estamos en el primer elemento
void Dish::previousFood() {
	if (!foods_.empty() && currentFood != foods_.begin())
		currentFood--;
}
void Dish::render() {
	int i = height;
	for (auto i = foods_.begin(); i != foods_.end(); i++)
	{
		(*i)->draw();
	}
}