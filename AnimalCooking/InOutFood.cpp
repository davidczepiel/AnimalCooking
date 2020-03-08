#include "InOutFood.h"

InOutFood::InOutFood() :Component(ecs::InOutFood)
{

}

list<Food*> InOutFood::getList()
{
	return foods_;
}



bool InOutFood::isEmpty()
{
	return foods_.empty();
}
// si la lista estaba vacía pone el iterador al principio
void InOutFood::addFood(Food* f)
{
	if (f != nullptr) {
		foods_.push_back(f);
		if (foods_.size() == 1)
		{
			currentFood = foods_.begin();
		}
	}

}

Food* InOutFood::takeFood()
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
void InOutFood::nextFood() {
	if (!foods_.empty() && currentFood != (--foods_.end()))
		currentFood++;
}
//Comprobamos que no está la lista vacía y no estamos en el primer elemento
void InOutFood::previousFood() {
	if (!foods_.empty() && currentFood != foods_.begin())
		currentFood--;
}