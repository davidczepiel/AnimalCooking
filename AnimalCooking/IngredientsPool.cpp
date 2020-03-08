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
	cout << "ingrediente anadido" << endl;
	ingredients_.push_back(i);
	i->setInVector(--ingredients_.end(), this);
}

void IngredientsPool::clearIngredients()
{
	for (int i = 0; i < ingredients_.size(); ++i) {
		delete ingredients_[i];
	}

	ingredients_.clear();
}
