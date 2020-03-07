#include "IngredientsPool.h"

IngredientsPool::IngredientsPool() : Component(ecs::IngredientsPool), pool_(30, [](Ingredient* i) {return i->inUse(); })
{
	for (int i = 0; i < 30; ++i) {
		Tomato* t = new Tomato();
		pool_.getPool()[i] = t;
	}
}

void IngredientsPool::init() {

}

void IngredientsPool::addIngredient()
{

}

