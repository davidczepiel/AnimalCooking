#pragma once
#include "Component.h"
#include "ObjectPool.h"

class Ingredient;

class IngredientsPool : public Component
{
public:
	IngredientsPool() : Component(ecs::IngredientsPool) {}
	~IngredientsPool();

	inline const std::vector<Ingredient*>& getPool() { return ingredients_; }

	void addIngredient(Ingredient* i);
	void deleteIngredient(vector<Ingredient*>::iterator it) { ingredients_.erase(it); }
	void clearIngredients();

private:
	std::vector<Ingredient*> ingredients_;
};


