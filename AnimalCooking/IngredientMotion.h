#pragma once

#include "Component.h"
#include "IngredientsPool.h"
#include "Physics.h"

class IngredientMotion : public Component
{
private:
	IngredientsPool* pool_;
	Physics* ph;

public:
	IngredientMotion() : Component(ecs::IngredientMotion), pool_(nullptr) { }
	virtual ~IngredientMotion() { }
	void init() override;
	void update() override;
};