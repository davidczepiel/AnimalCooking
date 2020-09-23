#include "IngredientsPool.h"
#include "Ingredient.h"
#include "Entity.h"

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
	i->setInVector(it, this,GETCMP2(entity_,AIIngredient));
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
	delete ingredients_.back();
	ingredients_.pop_back();
}