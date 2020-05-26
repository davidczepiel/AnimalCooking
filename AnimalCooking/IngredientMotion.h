#pragma once

#include "Component.h"
#include "IngredientsPool.h"

class IngredientMotion : public Component
{

public:
	IngredientMotion() : Component(ecs::IngredientMotion), pool_(nullptr) { }
	virtual ~IngredientMotion() { }
	void init() override;
	void update() override;

private:
	IngredientsPool* pool_;
};