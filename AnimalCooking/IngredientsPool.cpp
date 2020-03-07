#include "IngredientsPool.h"

IngredientsPool::IngredientsPool() : Component(ecs::IngredientsPool), pool_(30, [](Ingredient* i) {return i->inUse(); })
{
}

void IngredientsPool::addIngredient()
{

}

