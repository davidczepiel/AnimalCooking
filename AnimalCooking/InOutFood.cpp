#include "InOutFood.h"

InOutFood::InOutFood() :Component(ecs::InOutFood)
{

}

vector<Food*>* InOutFood:: getPool()
{
	return &foods_;
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
	if(f!=nullptr) foods_.push_back(f);  
}

void InOutFood::takeFood(Food* f)
{
	//foods_.erase();
}