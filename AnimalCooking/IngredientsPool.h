#pragma once
#include "Component.h"
#include "ObjectPool.h"

using namespace std;

class Ingredient;

class IngredientsPool : public Component
{
public:
	IngredientsPool() : Component(ecs::IngredientsPool) {
		ingredients_.reserve(10);
	}
	~IngredientsPool();

	inline const std::vector<Ingredient*>& getPool() { return ingredients_; }

	void addIngredient(Ingredient* i);
	void deleteIngredient(vector<Ingredient*>::iterator it) {
		std::vector<Ingredient*>::iterator i = ingredients_.end();
		--i;
		if (i != it)
			iter_swap(it, i);

		ingredients_.pop_back();
	}
	void clearIngredients();

private:
	std::vector<Ingredient*> ingredients_;
};


