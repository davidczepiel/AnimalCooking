#pragma once
#include "Component.h"
#include "ObjectPool.h"

using namespace std;

class Ingredient;

class IngredientsPool : public Component
{
public:
	IngredientsPool() : Component(ecs::IngredientsPool) {
		ingredients_.reserve(20);
	}
	~IngredientsPool();

	inline const std::vector<Ingredient*>& getPool() { return ingredients_; }

	void addIngredient(Ingredient* i);
	void deleteIngredient(vector<Ingredient*>::iterator it);
	void clearIngredients();

private:
	std::vector<Ingredient*> ingredients_;
};


