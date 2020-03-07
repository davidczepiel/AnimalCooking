#pragma once

#include "Component.h"
#include "Ingredient.h"

class IngredientMotion : public Component
{
private:
	vector<Ingredient*> pool_;

public:
	IngredientMotion() : Component(ecs::IngredientMotion) { }
	virtual ~IngredientMotion() { }
	void init() override;
	void draw() override;
};