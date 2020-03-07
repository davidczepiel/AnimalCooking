#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Ingredient.h"

class IngredientsPool : public Component
{
public:
	IngredientsPool();
	~IngredientsPool() {}

	void init() override;
	void update() override{};
	void draw() override{};
	void addIngredient();
	inline std::vector<Ingredient*> getPool() { return pool_.getPool(); }
private:
	ObjectPool<Ingredient> pool_;
};


