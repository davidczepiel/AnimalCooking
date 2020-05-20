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
	ingredients_.emplace_back(i);
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

void IngredientsPool::deleteIngredient(vector<Ingredient*>::iterator it) {

	Ingredient* i = *(--ingredients_.end());
	i->setIt(it);
	iter_swap(it, --ingredients_.end());
	ingredients_.pop_back();
}