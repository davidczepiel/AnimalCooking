#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Ingredient.h"

class IngredientsPool : public Component
{
public:
	IngredientsPool();
	~IngredientsPool() {}

	void init() override {};
	void update() override{};
	void draw() override{};

	template<typename I>
	void addIngredient(double w, double h, Vector2D pos, Vector2D vel);

	inline std::vector<Ingredient*> getPool() { return pool_.getPool(); }
private:
	ObjectPool<Ingredient> pool_;
};


