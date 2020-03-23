#include "IngredientsPool.h"
#include "Ingredient.h"

IngredientsPool::~IngredientsPool()
{
	for (int i = 0; i < ingredients_.size(); ++i) {
		delete ingredients_[i];
	}
}

void IngredientsPool::addIngredient(Ingredient* i)
{
	ingredients_.push_back(i);
	std::vector<Ingredient*>::iterator it = ingredients_.end();
	--it;
	i->setInVector(it, this);
}

void IngredientsPool::clearIngredients()
{
	for (int i = 0; i < ingredients_.size(); ++i) {
		delete ingredients_[i];
	}

	ingredients_.clear();
}
