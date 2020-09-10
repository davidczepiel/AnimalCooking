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

	void addIngredient(Ingredient* i);
	void deleteIngredient(vector<Ingredient*>::iterator it);
	void clearIngredients();

	inline const std::vector<Ingredient*>& getPool() { return ingredients_; }
	//inline const std::vector<Ingredient*>& getPool() { return ingredients_; }


private:
	std::vector<Ingredient*> ingredients_;
};


