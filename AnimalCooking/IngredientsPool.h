#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Ingredient.h"

class IngredientsPool : public Component
{
public:
	IngredientsPool();
	~IngredientsPool() {}
	void addIngredient();
	void getPool();
private:
	ObjectPool<Ingredient> pool_;
};

