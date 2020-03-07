#pragma once

#include "Component.h"
#include "Ingredient.h"

class IngredientViewer : public Component
{
private:
	vector<Ingredient*> pool_;

public:
	IngredientViewer() : Component(ecs::IngredientViewer) { }
	virtual ~IngredientViewer() { }
	void init() override;
	void draw() override;
};