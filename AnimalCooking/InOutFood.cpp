#include "InOutFood.h"

InOutFood::InOutFood() :Component(ecs::InOutFood),currentFood(foods_.end())
{

}

list<Food*> InOutFood::getList()
{
	return foods_;
}

void InOutFood::setEmpty(bool b)
{
	empty = b;
}

bool InOutFood::isEmpty()
{
	return empty;
}

void InOutFood::addFood(Food* f)
{
	if (f != nullptr) {
		foods_.push_back(f);
		if(foods_.size()==1)
		{
		empty = false;
		currentFood = foods_.begin();
		}
	}
	
}

Food* InOutFood::takeFood()
{
	if (currentFood!=foods_.begin() && currentFood!=foods_.end()) {
		foods_.remove(*currentFood);
		if (foods_.empty())
			empty = true;
	}
	return *currentFood;
}
void InOutFood::nextFood() {
	if (currentFood != foods_.end())
		currentFood++;
}
void InOutFood::previousFood() {
	if (currentFood != foods_.begin())
		currentFood--;
}